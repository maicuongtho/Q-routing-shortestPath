//
// Copyright (C) 2013 OpenSim Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later
//


#include "NeighborTable.h"

#include "inet/common/stlutils.h"

namespace inet {

std::vector<L3Address> NeighborTable::getAddresses() const
{
    std::vector<L3Address> addresses;
    for (const auto& elem : addressToPositionMap)
        addresses.push_back(elem.first);
    return addresses;
}

bool NeighborTable::hasPosition(const L3Address& address) const
{
    return containsKey(addressToPositionMap, address);
}

Coord NeighborTable::getPosition(const L3Address& address) const
{
    auto it = addressToPositionMap.find(address);
    return (it == addressToPositionMap.end()) ? Coord(NaN, NaN, NaN) : it->second.second;
}

void NeighborTable::setPosition(const L3Address& address, const Coord& coord)
{
    ASSERT(!address.isUnspecified());
    addressToPositionMap[address] = AddressToPositionMapValue(simTime(), coord);
}

void NeighborTable::removePosition(const L3Address& address)
{
    auto it = addressToPositionMap.find(address);
    addressToPositionMap.erase(it);
}

//void NeighborTable::removeOldPositions(simtime_t timestamp)
//{
//    for (auto it = addressToPositionMap.begin(); it != addressToPositionMap.end();)
//        if (it->second.first <= timestamp)
//            addressToPositionMap.erase(it++);
//        else
//            it++;
//
//}
std::vector<L3Address> NeighborTable::removeOldPositions(simtime_t timestamp)
{
    std::vector<L3Address> listNeighborNode_Deleted;
    for (auto it = addressToPositionMap.begin(); it != addressToPositionMap.end();)
        if (it->second.first <= timestamp)
        {
            listNeighborNode_Deleted.push_back(it->first);
            addressToPositionMap.erase(it++);
        }
        else
            it++;
    return listNeighborNode_Deleted;
}
void NeighborTable::clear()
{
    addressToPositionMap.clear();
}

simtime_t NeighborTable::getOldestPosition() const
{
    simtime_t oldestPosition = SimTime::getMaxTime();
    for (const auto& elem : addressToPositionMap) {
        const simtime_t& time = elem.second.first;
        if (time < oldestPosition)
            oldestPosition = time;
    }
    return oldestPosition;
}

std::ostream& operator<<(std::ostream& o, const NeighborTable& t)
{
    o << "============BẢNG LÁNG GIỀNG==========\n";
    for (auto elem : t.addressToPositionMap) {
        o << elem.first << ":(" << elem.second.first << ";" << elem.second.second << ")\n ";
    }
    o << "======================================\n";
    return o;
}

} // namespace inet

