//
// Copyright (C) 2013 OpenSim Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later
//


#include "QlHC.h"

#include <algorithm>

#include "inet/common/INETUtils.h"
#include "inet/common/IProtocolRegistrationListener.h"
#include "inet/common/ModuleAccess.h"
#include "inet/common/ProtocolTag_m.h"
#include "inet/common/lifecycle/ModuleOperations.h"
#include "inet/linklayer/common/InterfaceTag_m.h"
#include "inet/networklayer/common/HopLimitTag_m.h"
#include "inet/networklayer/common/IpProtocolId_m.h"
#include "inet/networklayer/common/L3AddressTag_m.h"
#include "inet/networklayer/common/L3Tools.h"
#include "inet/networklayer/common/NextHopAddressTag_m.h"
#include "inet/networklayer/contract/IInterfaceTable.h"

#ifdef INET_WITH_IPv4
#include "inet/networklayer/ipv4/Ipv4Header_m.h"
#endif

#ifdef INET_WITH_IPv6
#include "inet/networklayer/ipv6/Ipv6ExtensionHeaders_m.h"
#include "inet/networklayer/ipv6/Ipv6InterfaceData.h"
#endif

#ifdef INET_WITH_NEXTHOP
#include "inet/networklayer/nexthop/NextHopForwardingHeader_m.h"
#endif

namespace inet {

Define_Module(QlHC);


QlHC::QlHC()
{
    srand((unsigned int)time(0));
}

QlHC::~QlHC()
{
    cancelAndDelete(beaconTimer);
    cancelAndDelete(purgeNeighborsTimer);
}

//
// module interface
//

void QlHC::initialize(int stage)
{
    if (stage == INITSTAGE_ROUTING_PROTOCOLS)
        addressType = getSelfAddress().getAddressType();

    RoutingProtocolBase::initialize(stage);

    if (stage == INITSTAGE_LOCAL) {
        // QlHC parameters
        const char *planarizationModeString = par("planarizationMode");
        if (!strcmp(planarizationModeString, ""))
            planarizationMode = GPSR_NO_PLANARIZATION;
        else if (!strcmp(planarizationModeString, "GG"))
            planarizationMode = GPSR_GG_PLANARIZATION;
        else if (!strcmp(planarizationModeString, "RNG"))
            planarizationMode = GPSR_RNG_PLANARIZATION;
        else
            throw cRuntimeError("Unknown planarization mode");
        interfaces = par("interfaces");
        beaconInterval = par("beaconInterval");
        maxJitter = par("maxJitter");
        neighborValidityInterval = par("neighborValidityInterval");
        displayBubbles = par("displayBubbles");
        // context
        host = getContainingNode(this);
        interfaceTable.reference(this, "interfaceTableModule", true);
        outputInterface = par("outputInterface");
        mobility = check_and_cast<IMobility *>(host->getSubmodule("mobility"));
        routingTable.reference(this, "routingTableModule", true);
        networkProtocol.reference(this, "networkProtocolModule", true);
        // internal
        beaconTimer = new cMessage("BeaconTimer");
        purgeNeighborsTimer = new cMessage("PurgeNeighborsTimer");
        // packet size
        positionByteLength = par("positionByteLength");
        // KLUDGE implement position registry protocol
        globalPositionTable.clear();

        Ipv4Address addr;
        L3Address addrL3;
        for (int i=0; i<50; i++){
                addr.set(172, 16, 1, 1+i);
                addrL3.set(addr);
                networkNodes.push_back(addrL3);
          }
        addr.set(172, 16, 1, 200);
        addrL3.set(addr);
        networkNodes.push_back(addrL3);
        addr.set(172, 16, 1, 201);
        addrL3.set(addr);
        networkNodes.push_back(addrL3);
    }
    else if (stage == INITSTAGE_ROUTING_PROTOCOLS) {
        registerProtocol(Protocol::manet, gate("ipOut"), gate("ipIn"));
        host->subscribe(linkBrokenSignal, this);
        networkProtocol->registerHook(0, this);
        WATCH(neighborPositionTable);
    }
}

void QlHC::handleMessageWhenUp(cMessage *message)
{
    if (message->isSelfMessage())
        processSelfMessage(message);
    else
        processMessage(message);
}

//
// handling messages
//

void QlHC::processSelfMessage(cMessage *message)
{
    if (message == beaconTimer)
        processBeaconTimer();
    else if (message == purgeNeighborsTimer)
        processPurgeNeighborsTimer();
    else
        throw cRuntimeError("Unknown self message");
}

void QlHC::processMessage(cMessage *message)
{
    if (auto pk = dynamic_cast<Packet *>(message))
        processUdpPacket(pk);
    else
        throw cRuntimeError("Unknown message");
}

//
// beacon timers
//

void QlHC::scheduleBeaconTimer()
{
    EV_DEBUG << "Scheduling beacon timer" << endl;
    scheduleAfter(beaconInterval + uniform(-1, 1) * maxJitter, beaconTimer);
}

void QlHC::processBeaconTimer()
{
    EV_DEBUG << "Processing beacon timer" << endl;
    const L3Address selfAddress = getSelfAddress();
    if (!selfAddress.isUnspecified()) {
        sendBeacon(createBeacon());
        storeSelfPositionInGlobalRegistry();
    }
    scheduleBeaconTimer();
    schedulePurgeNeighborsTimer();
}

//
// handling purge neighbors timers
//

void QlHC::schedulePurgeNeighborsTimer()
{
    EV_DEBUG << "Scheduling purge neighbors timer" << endl;
    simtime_t nextExpiration = getNextNeighborExpiration();
    if (nextExpiration == SimTime::getMaxTime()) {
        if (purgeNeighborsTimer->isScheduled())
            cancelEvent(purgeNeighborsTimer);
    }
    else {
        if (!purgeNeighborsTimer->isScheduled())
            scheduleAt(nextExpiration, purgeNeighborsTimer);
        else {
            if (purgeNeighborsTimer->getArrivalTime() != nextExpiration) {
                rescheduleAt(nextExpiration, purgeNeighborsTimer);
            }
        }
    }
}

void QlHC::processPurgeNeighborsTimer()
{
    EV_DEBUG << "Processing purge neighbors timer" << endl;
    purgeNeighbors();
    schedulePurgeNeighborsTimer();
}

//
// handling UDP packets
//

void QlHC::sendUdpPacket(Packet *packet)
{
    send(packet, "ipOut");
}

void QlHC::processUdpPacket(Packet *packet)
{
    const char *packetName =packet->getName();
    EV_INFO<<"processUdpPacket: "<<packetName <<endl;
    packet->popAtFront<UdpHeader>();
    if(strcmp(packetName,"Hello")==0)
           processBeacon(packet);

    if(strcmp(packetName,"QlHCACK")==0)
           recv_qrouting_ack(packet);

   schedulePurgeNeighborsTimer();
}

//
// handling beacons
//

const Ptr<QlHCBeacon> QlHC::createBeacon()
{
    const auto& beacon = makeShared<QlHCBeacon>();
    beacon->setAddress(getSelfAddress());
    beacon->setPosition(mobility->getCurrentPosition());
    beacon->setChunkLength(B(getSelfAddress().getAddressType()->getAddressByteLength() + positionByteLength));
    return beacon;
}

void QlHC::sendBeacon(const Ptr<QlHCBeacon>& beacon)
{
    EV_INFO << "Sending beacon: address = " << beacon->getAddress() << ", position = " << beacon->getPosition() << endl;
    Packet *udpPacket = new Packet("Hello");
    udpPacket->insertAtBack(beacon);
    auto udpHeader = makeShared<UdpHeader>();
    udpHeader->setSourcePort(QLHC_UDP_PORT);
    udpHeader->setDestinationPort(QLHC_UDP_PORT);
    udpHeader->setCrcMode(CRC_DISABLED);
    udpPacket->insertAtFront(udpHeader);
    auto addresses = udpPacket->addTag<L3AddressReq>();
    addresses->setSrcAddress(getSelfAddress());
    addresses->setDestAddress(addressType->getLinkLocalManetRoutersMulticastAddress());
    udpPacket->addTag<HopLimitReq>()->setHopLimit(255);
    udpPacket->addTag<PacketProtocolTag>()->setProtocol(&Protocol::manet);
    udpPacket->addTag<DispatchProtocolReq>()->setProtocol(addressType->getNetworkProtocol());
    sendUdpPacket(udpPacket);
}

void QlHC::processBeacon(Packet *packet)
{
    const auto& beacon = packet->peekAtFront<QlHCBeacon>();
    L3Address nextHop = beacon->getAddress();
    EV_INFO << "Processing beacon: address = " << nextHop << ", position = " << beacon->getPosition() << endl;
    neighborPositionTable.setPosition(nextHop, beacon->getPosition());

    delete packet;

}

//
// handling packets
//

QlHCOption *QlHC::createGpsrOption(L3Address destination)
{
    QlHCOption *gpsrOption = new QlHCOption();
    gpsrOption->setRoutingMode(GPSR_GREEDY_ROUTING);
    gpsrOption->setDestinationPosition(lookupPositionInGlobalRegistry(destination));
    gpsrOption->setLength(computeOptionLength(gpsrOption));
    return gpsrOption;
}

int QlHC::computeOptionLength(QlHCOption *option)
{
    // routingMode
    int routingModeBytes = 1;
    // destinationPosition, perimeterRoutingStartPosition, perimeterRoutingForwardPosition
    int positionsBytes = 3 * positionByteLength;
    // currentFaceFirstSenderAddress, currentFaceFirstReceiverAddress, senderAddress
    int addressesBytes = 3 * getSelfAddress().getAddressType()->getAddressByteLength();
    // type and length
    int tlBytes = 1 + 1;

    return tlBytes + routingModeBytes + positionsBytes + addressesBytes;
}

//
// configuration
//

void QlHC::configureInterfaces()
{
    // join multicast groups
    cPatternMatcher interfaceMatcher(interfaces, false, true, false);
    for (int i = 0; i < interfaceTable->getNumInterfaces(); i++) {
        NetworkInterface *networkInterface = interfaceTable->getInterface(i);
        if (networkInterface->isMulticast() && interfaceMatcher.matches(networkInterface->getInterfaceName()))
            networkInterface->joinMulticastGroup(addressType->getLinkLocalManetRoutersMulticastAddress());
    }
}

//
// position
//

// KLUDGE implement position registry protocol
NeighborTable QlHC::globalPositionTable;

Coord QlHC::lookupPositionInGlobalRegistry(const L3Address& address) const
{
    // KLUDGE implement position registry protocol
    return globalPositionTable.getPosition(address);
}

void QlHC::storePositionInGlobalRegistry(const L3Address& address, const Coord& position) const
{
    // KLUDGE implement position registry protocol
    globalPositionTable.setPosition(address, position);
}

void QlHC::storeSelfPositionInGlobalRegistry() const
{
    auto selfAddress = getSelfAddress();
    if (!selfAddress.isUnspecified())
        storePositionInGlobalRegistry(selfAddress, mobility->getCurrentPosition());
}


Coord QlHC::getNeighborPosition(const L3Address& address) const
{
    return neighborPositionTable.getPosition(address);
}

//
// address
//

std::string QlHC::getHostName() const
{
    return host->getFullName();
}

L3Address QlHC::getSelfAddress() const
{
    // TODO choose self address based on a new 'interfaces' parameter
    L3Address ret = routingTable->getRouterIdAsGeneric();
#ifdef INET_WITH_IPv6
    if (ret.getType() == L3Address::IPv6) {
        for (int i = 0; i < interfaceTable->getNumInterfaces(); i++) {
            NetworkInterface *ie = interfaceTable->getInterface(i);
            if ((!ie->isLoopback())) {
                if (auto ipv6Data = ie->findProtocolData<Ipv6InterfaceData>()) {
                    ret = ipv6Data->getPreferredAddress();
                    break;
                }
            }
        }
    }
#endif
    return ret;
}

L3Address QlHC::getSenderNeighborAddress(const Ptr<const NetworkHeaderBase>& networkHeader) const
{
    const QlHCOption *gpsrOption = getGpsrOptionFromNetworkDatagram(networkHeader);
    return gpsrOption->getSenderAddress();
}

//
// neighbor
//

simtime_t QlHC::getNextNeighborExpiration()
{
    simtime_t oldestPosition = neighborPositionTable.getOldestPosition();
    if (oldestPosition == SimTime::getMaxTime())
        return oldestPosition;
    else
        return oldestPosition + neighborValidityInterval;
}

void QlHC::purgeNeighbors()
{
    //neighborPositionTable.removeOldPositions(simTime() - neighborValidityInterval);
    std::vector<L3Address>  listNeighborNode_Deleted= neighborPositionTable.removeOldPositions(simTime() - neighborValidityInterval);
    for (const L3Address& nbDel : listNeighborNode_Deleted) {
           qTable.Delete(nbDel);
     }
}
double genRandomNumber(){
    std::mt19937 rng(std::random_device{}());
    std::uniform_real_distribution<float> dist(0.0f, 1.0f);
    return dist(rng);
}
//
// next hop
//
L3Address QlHC::findNextHop(const L3Address& destination, QlHCOption *qlhcOption)
{
    L3Address selfAddress = getSelfAddress();
    L3Address sender = qlhcOption->getSenderAddress();
    L3Address bestNeighbor;

    std::vector<L3Address> actionList = neighborPositionTable.getAddresses();
    for (auto action: actionList)                           //Kiểm tra các action
        if (!qTable.ExistedEntry(destination,action))       //nếu Q-table chưa có cặp Q(s,a)
             qTable.AddNewEntry(destination, action, 100);  //Cập nhật cặp (s,a) mới

    if (neighborPositionTable.hasPosition(destination))  {
        qTable.UpdateQnew(destination, destination, 1);
        bestNeighbor= destination;
    }
    else{
        epsilon = min_epsilon + (max_epsilon - min_epsilon)* exp(-decay_rate* current_episode);
        float random_value = genRandomNumber();
        if (epsilon< random_value)
            bestNeighbor = qTable.getHopMinQ(sender,destination);  // Exploitation
        else
            bestNeighbor = qTable.getHopRandom(sender,destination); //Explorarion
    }
    if (current_episode <max_train_episodes) current_episode++;
    return bestNeighbor;
}

//
// routing
//

INetfilter::IHook::Result QlHC::routeDatagram(Packet *datagram, QlHCOption *gpsrOption)
{
    const auto& networkHeader = getNetworkProtocolHeader(datagram);
    const L3Address& source = networkHeader->getSourceAddress();
    const L3Address& destinationDataPacket = networkHeader->getDestinationAddress();
    EV_INFO << "Finding next hop: Source = " << source << ", destination = " << destinationDataPacket << endl;
    auto nextHop = findNextHop(destinationDataPacket, gpsrOption);
    datagram->addTagIfAbsent<NextHopAddressReq>()->setNextHopAddress(nextHop);
    if (nextHop.isUnspecified()) {
        EV_WARN << "No next hop found, dropping packet: source = " << source << ", destination = " << destinationDataPacket << endl;
        send_qrouting_ack(gpsrOption->getSenderAddress(),false, nextHop, destinationDataPacket);
        return DROP;
    }
    else {
        send_qrouting_ack( gpsrOption->getSenderAddress() ,true, nextHop, destinationDataPacket);
        EV_INFO << "Next hop found: source = " << source << ", destination = " << destinationDataPacket << ", nextHop: " << nextHop << endl;
        gpsrOption->setSenderAddress(getSelfAddress());
        auto networkInterface = CHK(interfaceTable->findInterfaceByName(outputInterface));
        datagram->addTagIfAbsent<InterfaceReq>()->setInterfaceId(networkInterface->getInterfaceId());
        return ACCEPT;
    }
}
//Generate and send ACK at action node Y
void QlHC::send_qrouting_ack(const L3Address& backtoHop,bool isReward,const L3Address& nextHop, const L3Address& destinationUDPdata) {
    //====================================================================================================
    double rewardValue;
    if (!isReward) rewardValue = 0;
    else rewardValue = 1;
    EV<<"Gửi ACK, vởi R=" <<  rewardValue;
    EV<<"\nBảng Q " << qTable;

    double QvalueMin =qTable.getMinQ(destinationUDPdata);
    EV<<"\n Qmin để ACK " << QvalueMin;

     //1. Creat ACK packet
    const auto& ack = makeShared<QlHCACK>();
    ack->setAddress(backtoHop);
    ack->setRewardValue(rewardValue);
    ack->setMinQvalue2Destination(QvalueMin);
    ack->setDesinationAddressUDPdata(destinationUDPdata);
    ack->setChunkLength(B(getSelfAddress().getAddressType()->getAddressByteLength() + positionByteLength));

    //2. Send
    EV_INFO << "Sending ACK from:  address = " <<getSelfAddress() << endl;
    Packet *udpPacket = new Packet("QlHCACK");
    udpPacket->setName("QlHCACK");
    udpPacket->insertAtBack(ack);
    auto udpHeader = makeShared<UdpHeader>();
    udpHeader->setSourcePort(QLHC_UDP_PORT);
    udpHeader->setDestinationPort(QLHC_UDP_PORT);
    udpHeader->setCrcMode(CRC_DISABLED);
    udpPacket->insertAtFront(udpHeader);
    auto addresses = udpPacket->addTag<L3AddressReq>();
    addresses->setSrcAddress(getSelfAddress());
    addresses->setDestAddress(backtoHop);
    udpPacket->addTag<HopLimitReq>()->setHopLimit(1);
    udpPacket->addTag<PacketProtocolTag>()->setProtocol(&Protocol::manet);
    udpPacket->addTag<DispatchProtocolReq>()->setProtocol(addressType->getNetworkProtocol());
    sendUdpPacket(udpPacket);
}
// Processed at node X when receiving ACK from node Y (action, or ackSender)
void QlHC::recv_qrouting_ack(Packet* p) {
    const auto& networkHeader = getNetworkProtocolHeader(p);
    L3Address ackSender = networkHeader->getSourceAddress(); // action
    // Cập nhật lại bảng Q
    const auto& ack = p->peekAtFront<QlHCACK>();
    EV_INFO << "Processing ACK: from address = " << ackSender << endl;
    double rewardReceived = ack->getRewardValue();
    double Qvalue_min_Y_D= ack->getMinQvalue2Destination();

    EV<<"Thưởng nhận được: " <<rewardReceived;
    EV<<"\nQMin nhận được: " <<Qvalue_min_Y_D;

    EV<<"\nBảng Q cũ \n" << qTable<<"\n";

    L3Address destinationUDPdata = ack->getDesinationAddressUDPdata(); //destination
    if (qTable.ExistedEntry(destinationUDPdata, ackSender))  {
        double Qvalue_X_D_via_Y_old =qTable.getOldMinQ(ackSender,destinationUDPdata);
        double TD_taget = rewardReceived+discountRate*Qvalue_min_Y_D;
        double TD_Error = TD_taget  - Qvalue_X_D_via_Y_old;
        double Qvalue_X_D_via_Y_new = Qvalue_X_D_via_Y_old +learningRate*TD_Error;
        qTable.UpdateQnew(ackSender,destinationUDPdata, Qvalue_X_D_via_Y_new);
    }
    EV<<"Bảng Q mới \n" << qTable<<"\n";
   delete p;
}

INetfilter::IHook::Result QlHC::routeDatagramACK(Packet *datagram, QlHCOption *gpsrOption)
{
    const auto& networkHeader = getNetworkProtocolHeader(datagram);
    const L3Address& source = networkHeader->getSourceAddress();
    const L3Address& destination = networkHeader->getDestinationAddress();
    L3Address nextHop=destination;

    EV_INFO << "Next (ACK) hop found: source = " << source << ", destination = " << destination << ", nextHop: " << nextHop << endl;
    auto networkInterface = CHK(interfaceTable->findInterfaceByName(outputInterface));
    datagram->addTagIfAbsent<InterfaceReq>()->setInterfaceId(networkInterface->getInterfaceId());
    return ACCEPT;
}

INetfilter::IHook::Result QlHC::routeMyOwnDatagram(Packet *datagram, QlHCOption *gpsrOption)
{
    // Chú ý có 2 loại dataGram: UDP và ACK, mỗi cái đều có nguồn: nút tạo gói, đích đến của gói
    const auto& networkHeader = getNetworkProtocolHeader(datagram);
    const L3Address& source = networkHeader->getSourceAddress();
    const L3Address& destination = networkHeader->getDestinationAddress();
    const char* protocolName = networkHeader->getProtocol()->getName();
    L3Address nextHop;
    EV_INFO << "Finding next hop for my UDP Data: source = " << source << ", destination = " << destination << endl;

    nextHop =findNextHop(destination, gpsrOption);

    datagram->addTagIfAbsent<NextHopAddressReq>()->setNextHopAddress(nextHop);
    if (nextHop.isUnspecified() || (gpsrOption->getSenderAddress()==nextHop)) {
        EV_WARN << "No next hop found, dropping packet: source = " << source << ", destination = " << destination << endl;
        if (displayBubbles && hasGUI()) getContainingNode(host)->bubble("No next hop found, dropping packet");
        return DROP;
    }
    else {
        EV_INFO << "Next hop found: source = " << source << ", destination = " << destination << ", nextHop: " << nextHop << endl;
        auto networkInterface = CHK(interfaceTable->findInterfaceByName(outputInterface));
        gpsrOption->setSenderAddress(getSelfAddress());
        datagram->addTagIfAbsent<InterfaceReq>()->setInterfaceId(networkInterface->getInterfaceId());
        return ACCEPT;
    }
}
void QlHC::setGpsrOptionOnNetworkDatagram(Packet *packet, const Ptr<const NetworkHeaderBase>& networkHeader, QlHCOption *gpsrOption)
{
    packet->trimFront();
#ifdef INET_WITH_IPv4
    if (dynamicPtrCast<const Ipv4Header>(networkHeader)) {
        auto ipv4Header = removeNetworkProtocolHeader<Ipv4Header>(packet);
        gpsrOption->setType(IPOPTION_TLV_GPSR);
        B oldHlen = ipv4Header->calculateHeaderByteLength();
        ASSERT(ipv4Header->getHeaderLength() == oldHlen);
        ipv4Header->addOption(gpsrOption);
        B newHlen = ipv4Header->calculateHeaderByteLength();
        ipv4Header->setHeaderLength(newHlen);
        ipv4Header->addChunkLength(newHlen - oldHlen);
        ipv4Header->setTotalLengthField(ipv4Header->getTotalLengthField() + newHlen - oldHlen);
        insertNetworkProtocolHeader(packet, Protocol::ipv4, ipv4Header);
    }
    else
#endif
#ifdef INET_WITH_IPv6
    if (dynamicPtrCast<const Ipv6Header>(networkHeader)) {
        auto ipv6Header = removeNetworkProtocolHeader<Ipv6Header>(packet);
        gpsrOption->setType(IPv6TLVOPTION_TLV_GPSR);
        B oldHlen = ipv6Header->calculateHeaderByteLength();
        Ipv6HopByHopOptionsHeader *hdr = check_and_cast_nullable<Ipv6HopByHopOptionsHeader *>(ipv6Header->findExtensionHeaderByTypeForUpdate(IP_PROT_IPv6EXT_HOP));
        if (hdr == nullptr) {
            hdr = new Ipv6HopByHopOptionsHeader();
            hdr->setByteLength(B(8));
            ipv6Header->addExtensionHeader(hdr);
        }
        hdr->getTlvOptionsForUpdate().appendTlvOption(gpsrOption);
        hdr->setByteLength(B(utils::roundUp(2 + B(hdr->getTlvOptions().getLength()).get(), 8)));
        B newHlen = ipv6Header->calculateHeaderByteLength();
        ipv6Header->addChunkLength(newHlen - oldHlen);
        insertNetworkProtocolHeader(packet, Protocol::ipv6, ipv6Header);
    }
    else
#endif
#ifdef INET_WITH_NEXTHOP
    if (dynamicPtrCast<const NextHopForwardingHeader>(networkHeader)) {
        auto nextHopHeader = removeNetworkProtocolHeader<NextHopForwardingHeader>(packet);
        gpsrOption->setType(NEXTHOP_TLVOPTION_TLV_GPSR);
        int oldHlen = nextHopHeader->getTlvOptions().getLength();
        nextHopHeader->getTlvOptionsForUpdate().appendTlvOption(gpsrOption);
        int newHlen = nextHopHeader->getTlvOptions().getLength();
        nextHopHeader->addChunkLength(B(newHlen - oldHlen));
        insertNetworkProtocolHeader(packet, Protocol::nextHopForwarding, nextHopHeader);
    }
    else
#endif
    {
    }
}

const QlHCOption *QlHC::findGpsrOptionInNetworkDatagram(const Ptr<const NetworkHeaderBase>& networkHeader) const
{
    const QlHCOption *gpsrOption = nullptr;

#ifdef INET_WITH_IPv4
    if (auto ipv4Header = dynamicPtrCast<const Ipv4Header>(networkHeader)) {
        gpsrOption = check_and_cast_nullable<const QlHCOption *>(ipv4Header->findOptionByType(IPOPTION_TLV_GPSR));
    }
    else
#endif
#ifdef INET_WITH_IPv6
    if (auto ipv6Header = dynamicPtrCast<const Ipv6Header>(networkHeader)) {
        const Ipv6HopByHopOptionsHeader *hdr = check_and_cast_nullable<const Ipv6HopByHopOptionsHeader *>(ipv6Header->findExtensionHeaderByType(IP_PROT_IPv6EXT_HOP));
        if (hdr != nullptr) {
            int i = (hdr->getTlvOptions().findByType(IPv6TLVOPTION_TLV_GPSR));
            if (i >= 0)
                gpsrOption = check_and_cast<const QlHCOption *>(hdr->getTlvOptions().getTlvOption(i));
        }
    }
    else
#endif
#ifdef INET_WITH_NEXTHOP
    if (auto nextHopHeader = dynamicPtrCast<const NextHopForwardingHeader>(networkHeader)) {
        int i = (nextHopHeader->getTlvOptions().findByType(NEXTHOP_TLVOPTION_TLV_GPSR));
        if (i >= 0)
            gpsrOption = check_and_cast<const QlHCOption *>(nextHopHeader->getTlvOptions().getTlvOption(i));
    }
    else
#endif
    {
    }
    return gpsrOption;
}

QlHCOption *QlHC::findGpsrOptionInNetworkDatagramForUpdate(const Ptr<NetworkHeaderBase>& networkHeader)
{
    QlHCOption *gpsrOption = nullptr;

#ifdef INET_WITH_IPv4
    if (auto ipv4Header = dynamicPtrCast<Ipv4Header>(networkHeader)) {
        gpsrOption = check_and_cast_nullable<QlHCOption *>(ipv4Header->findMutableOptionByType(IPOPTION_TLV_GPSR));
    }
    else
#endif
#ifdef INET_WITH_IPv6
    if (auto ipv6Header = dynamicPtrCast<Ipv6Header>(networkHeader)) {
        Ipv6HopByHopOptionsHeader *hdr = check_and_cast_nullable<Ipv6HopByHopOptionsHeader *>(ipv6Header->findExtensionHeaderByTypeForUpdate(IP_PROT_IPv6EXT_HOP));
        if (hdr != nullptr) {
            int i = (hdr->getTlvOptions().findByType(IPv6TLVOPTION_TLV_GPSR));
            if (i >= 0)
                gpsrOption = check_and_cast<QlHCOption *>(hdr->getTlvOptionsForUpdate().getTlvOptionForUpdate(i));
        }
    }
    else
#endif
#ifdef INET_WITH_NEXTHOP
    if (auto nextHopHeader = dynamicPtrCast<NextHopForwardingHeader>(networkHeader)) {
        int i = (nextHopHeader->getTlvOptions().findByType(NEXTHOP_TLVOPTION_TLV_GPSR));
        if (i >= 0)
            gpsrOption = check_and_cast<QlHCOption *>(nextHopHeader->getTlvOptionsForUpdate().getTlvOptionForUpdate(i));
    }
    else
#endif
    {
    }
    return gpsrOption;
}

const QlHCOption *QlHC::getGpsrOptionFromNetworkDatagram(const Ptr<const NetworkHeaderBase>& networkHeader) const
{
    const QlHCOption *gpsrOption = findGpsrOptionInNetworkDatagram(networkHeader);
    if (gpsrOption == nullptr)
        throw cRuntimeError("QlHC option not found in datagram!");
    return gpsrOption;
}

QlHCOption *QlHC::getGpsrOptionFromNetworkDatagramForUpdate(const Ptr<NetworkHeaderBase>& networkHeader)
{
    QlHCOption *gpsrOption = findGpsrOptionInNetworkDatagramForUpdate(networkHeader);
    if (gpsrOption == nullptr)
        throw cRuntimeError("QlHC option not found in datagram!");
    return gpsrOption;
}

//
// netfilter
//

INetfilter::IHook::Result QlHC::datagramPreRoutingHook(Packet *datagram)
{
    Enter_Method("datagramPreRoutingHook");
    const auto& networkHeader = getNetworkProtocolHeader(datagram);
    const L3Address& destination = networkHeader->getDestinationAddress();
    if (destination.isMulticast() || destination.isBroadcast() || routingTable->isLocalAddress(destination))
    {
        EV<<"Tới đích rồi nha\n";

        return ACCEPT;
    }
    else {
        // KLUDGE this allows overwriting the GPSR option inside
        auto gpsrOption = const_cast<QlHCOption *>(getGpsrOptionFromNetworkDatagram(networkHeader));
        return routeDatagram(datagram, gpsrOption);
    }
}

INetfilter::IHook::Result QlHC::datagramLocalOutHook(Packet *packet)
{
    Enter_Method("datagramLocalOutHook");
    const auto& networkHeader = getNetworkProtocolHeader(packet);
    const L3Address& destination = networkHeader->getDestinationAddress();
    if (destination.isMulticast() || destination.isBroadcast() || routingTable->isLocalAddress(destination))
        return ACCEPT;
    else {
        QlHCOption *gpsrOption = createGpsrOption(networkHeader->getDestinationAddress());
        setGpsrOptionOnNetworkDatagram(packet, networkHeader, gpsrOption);
        const char* protocolName = networkHeader->getProtocol()->getName();
        if (strcmp(protocolName,"udp")==0)
            return routeMyOwnDatagram(packet, gpsrOption);  // Gửi gói DATA mình tạo ra
        else
            return routeDatagramACK(packet, gpsrOption);  // Gửi gói ACK mình tạo ra
    }
}

//
// lifecycle
//

void QlHC::handleStartOperation(LifecycleOperation *operation)
{
    configureInterfaces();
    storeSelfPositionInGlobalRegistry();
    scheduleBeaconTimer();
}

void QlHC::handleStopOperation(LifecycleOperation *operation)
{
    // TODO send a beacon to remove ourself from peers neighbor position table
    neighborPositionTable.clear();
    cancelEvent(beaconTimer);
    cancelEvent(purgeNeighborsTimer);
}

void QlHC::handleCrashOperation(LifecycleOperation *operation)
{
    neighborPositionTable.clear();

    cancelEvent(beaconTimer);
    cancelEvent(purgeNeighborsTimer);
}

//
// notification
//

void QlHC::receiveSignal(cComponent *source, simsignal_t signalID, cObject *obj, cObject *details)
{
    Enter_Method("%s", cComponent::getSignalName(signalID));

    if (signalID == linkBrokenSignal) {
        EV_WARN << "Received link break" << endl;
      // TODO remove the neighbor

    }
}

} // namespace inet

