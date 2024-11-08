//
// Generated file, do not edit! Created by opp_msgtool 6.0 from routing/qlhc/QlHC.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wshadow"
#  pragma clang diagnostic ignored "-Wconversion"
#  pragma clang diagnostic ignored "-Wunused-parameter"
#  pragma clang diagnostic ignored "-Wc++98-compat"
#  pragma clang diagnostic ignored "-Wunreachable-code-break"
#  pragma clang diagnostic ignored "-Wold-style-cast"
#elif defined(__GNUC__)
#  pragma GCC diagnostic ignored "-Wshadow"
#  pragma GCC diagnostic ignored "-Wconversion"
#  pragma GCC diagnostic ignored "-Wunused-parameter"
#  pragma GCC diagnostic ignored "-Wold-style-cast"
#  pragma GCC diagnostic ignored "-Wsuggest-attribute=noreturn"
#  pragma GCC diagnostic ignored "-Wfloat-conversion"
#endif

#include <iostream>
#include <sstream>
#include <memory>
#include <type_traits>
#include "QlHC_m.h"

namespace omnetpp {

// Template pack/unpack rules. They are declared *after* a1l type-specific pack functions for multiple reasons.
// They are in the omnetpp namespace, to allow them to be found by argument-dependent lookup via the cCommBuffer argument

// Packing/unpacking an std::vector
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::vector<T,A>& v)
{
    int n = v.size();
    doParsimPacking(buffer, n);
    for (int i = 0; i < n; i++)
        doParsimPacking(buffer, v[i]);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::vector<T,A>& v)
{
    int n;
    doParsimUnpacking(buffer, n);
    v.resize(n);
    for (int i = 0; i < n; i++)
        doParsimUnpacking(buffer, v[i]);
}

// Packing/unpacking an std::list
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::list<T,A>& l)
{
    doParsimPacking(buffer, (int)l.size());
    for (typename std::list<T,A>::const_iterator it = l.begin(); it != l.end(); ++it)
        doParsimPacking(buffer, (T&)*it);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::list<T,A>& l)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        l.push_back(T());
        doParsimUnpacking(buffer, l.back());
    }
}

// Packing/unpacking an std::set
template<typename T, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::set<T,Tr,A>& s)
{
    doParsimPacking(buffer, (int)s.size());
    for (typename std::set<T,Tr,A>::const_iterator it = s.begin(); it != s.end(); ++it)
        doParsimPacking(buffer, *it);
}

template<typename T, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::set<T,Tr,A>& s)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        T x;
        doParsimUnpacking(buffer, x);
        s.insert(x);
    }
}

// Packing/unpacking an std::map
template<typename K, typename V, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::map<K,V,Tr,A>& m)
{
    doParsimPacking(buffer, (int)m.size());
    for (typename std::map<K,V,Tr,A>::const_iterator it = m.begin(); it != m.end(); ++it) {
        doParsimPacking(buffer, it->first);
        doParsimPacking(buffer, it->second);
    }
}

template<typename K, typename V, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::map<K,V,Tr,A>& m)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        K k; V v;
        doParsimUnpacking(buffer, k);
        doParsimUnpacking(buffer, v);
        m[k] = v;
    }
}

// Default pack/unpack function for arrays
template<typename T>
void doParsimArrayPacking(omnetpp::cCommBuffer *b, const T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimPacking(b, t[i]);
}

template<typename T>
void doParsimArrayUnpacking(omnetpp::cCommBuffer *b, T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimUnpacking(b, t[i]);
}

// Default rule to prevent compiler from choosing base class' doParsimPacking() function
template<typename T>
void doParsimPacking(omnetpp::cCommBuffer *, const T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimPacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

template<typename T>
void doParsimUnpacking(omnetpp::cCommBuffer *, T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimUnpacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

}  // namespace omnetpp

namespace inet {

Register_Enum(inet::GpsrForwardingMode, (inet::GpsrForwardingMode::GPSR_GREEDY_ROUTING, inet::GpsrForwardingMode::GPSR_PERIMETER_ROUTING));

Register_Enum(inet::GpsrPlanarizationMode, (inet::GpsrPlanarizationMode::GPSR_NO_PLANARIZATION, inet::GpsrPlanarizationMode::GPSR_GG_PLANARIZATION, inet::GpsrPlanarizationMode::GPSR_RNG_PLANARIZATION));

Register_Class(QlHCBeacon)

QlHCBeacon::QlHCBeacon() : ::inet::FieldsChunk()
{
}

QlHCBeacon::QlHCBeacon(const QlHCBeacon& other) : ::inet::FieldsChunk(other)
{
    copy(other);
}

QlHCBeacon::~QlHCBeacon()
{
}

QlHCBeacon& QlHCBeacon::operator=(const QlHCBeacon& other)
{
    if (this == &other) return *this;
    ::inet::FieldsChunk::operator=(other);
    copy(other);
    return *this;
}

void QlHCBeacon::copy(const QlHCBeacon& other)
{
    this->address = other.address;
    this->position = other.position;
}

void QlHCBeacon::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::FieldsChunk::parsimPack(b);
    doParsimPacking(b,this->address);
    doParsimPacking(b,this->position);
}

void QlHCBeacon::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::FieldsChunk::parsimUnpack(b);
    doParsimUnpacking(b,this->address);
    doParsimUnpacking(b,this->position);
}

const L3Address& QlHCBeacon::getAddress() const
{
    return this->address;
}

void QlHCBeacon::setAddress(const L3Address& address)
{
    handleChange();
    this->address = address;
}

const Coord& QlHCBeacon::getPosition() const
{
    return this->position;
}

void QlHCBeacon::setPosition(const Coord& position)
{
    handleChange();
    this->position = position;
}

class QlHCBeaconDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_address,
        FIELD_position,
    };
  public:
    QlHCBeaconDescriptor();
    virtual ~QlHCBeaconDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(QlHCBeaconDescriptor)

QlHCBeaconDescriptor::QlHCBeaconDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::QlHCBeacon)), "inet::FieldsChunk")
{
    propertyNames = nullptr;
}

QlHCBeaconDescriptor::~QlHCBeaconDescriptor()
{
    delete[] propertyNames;
}

bool QlHCBeaconDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<QlHCBeacon *>(obj)!=nullptr;
}

const char **QlHCBeaconDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *QlHCBeaconDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int QlHCBeaconDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 2+base->getFieldCount() : 2;
}

unsigned int QlHCBeaconDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        0,    // FIELD_address
        FD_ISCOMPOUND,    // FIELD_position
    };
    return (field >= 0 && field < 2) ? fieldTypeFlags[field] : 0;
}

const char *QlHCBeaconDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "address",
        "position",
    };
    return (field >= 0 && field < 2) ? fieldNames[field] : nullptr;
}

int QlHCBeaconDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "address") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "position") == 0) return baseIndex + 1;
    return base ? base->findField(fieldName) : -1;
}

const char *QlHCBeaconDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::L3Address",    // FIELD_address
        "inet::Coord",    // FIELD_position
    };
    return (field >= 0 && field < 2) ? fieldTypeStrings[field] : nullptr;
}

const char **QlHCBeaconDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *QlHCBeaconDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int QlHCBeaconDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    QlHCBeacon *pp = omnetpp::fromAnyPtr<QlHCBeacon>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void QlHCBeaconDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    QlHCBeacon *pp = omnetpp::fromAnyPtr<QlHCBeacon>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'QlHCBeacon'", field);
    }
}

const char *QlHCBeaconDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    QlHCBeacon *pp = omnetpp::fromAnyPtr<QlHCBeacon>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string QlHCBeaconDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    QlHCBeacon *pp = omnetpp::fromAnyPtr<QlHCBeacon>(object); (void)pp;
    switch (field) {
        case FIELD_address: return pp->getAddress().str();
        case FIELD_position: return "";
        default: return "";
    }
}

void QlHCBeaconDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    QlHCBeacon *pp = omnetpp::fromAnyPtr<QlHCBeacon>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'QlHCBeacon'", field);
    }
}

omnetpp::cValue QlHCBeaconDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    QlHCBeacon *pp = omnetpp::fromAnyPtr<QlHCBeacon>(object); (void)pp;
    switch (field) {
        case FIELD_address: return omnetpp::toAnyPtr(&pp->getAddress()); break;
        case FIELD_position: return omnetpp::toAnyPtr(&pp->getPosition()); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'QlHCBeacon' as cValue -- field index out of range?", field);
    }
}

void QlHCBeaconDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    QlHCBeacon *pp = omnetpp::fromAnyPtr<QlHCBeacon>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'QlHCBeacon'", field);
    }
}

const char *QlHCBeaconDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_position: return omnetpp::opp_typename(typeid(Coord));
        default: return nullptr;
    };
}

omnetpp::any_ptr QlHCBeaconDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    QlHCBeacon *pp = omnetpp::fromAnyPtr<QlHCBeacon>(object); (void)pp;
    switch (field) {
        case FIELD_address: return omnetpp::toAnyPtr(&pp->getAddress()); break;
        case FIELD_position: return omnetpp::toAnyPtr(&pp->getPosition()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void QlHCBeaconDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    QlHCBeacon *pp = omnetpp::fromAnyPtr<QlHCBeacon>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'QlHCBeacon'", field);
    }
}

Register_Class(QlHCACK)

QlHCACK::QlHCACK() : ::inet::FieldsChunk()
{
}

QlHCACK::QlHCACK(const QlHCACK& other) : ::inet::FieldsChunk(other)
{
    copy(other);
}

QlHCACK::~QlHCACK()
{
}

QlHCACK& QlHCACK::operator=(const QlHCACK& other)
{
    if (this == &other) return *this;
    ::inet::FieldsChunk::operator=(other);
    copy(other);
    return *this;
}

void QlHCACK::copy(const QlHCACK& other)
{
    this->address = other.address;
    this->rewardValue = other.rewardValue;
    this->minQvalue2Destination = other.minQvalue2Destination;
    this->desinationAddressUDPdata = other.desinationAddressUDPdata;
}

void QlHCACK::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::FieldsChunk::parsimPack(b);
    doParsimPacking(b,this->address);
    doParsimPacking(b,this->rewardValue);
    doParsimPacking(b,this->minQvalue2Destination);
    doParsimPacking(b,this->desinationAddressUDPdata);
}

void QlHCACK::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::FieldsChunk::parsimUnpack(b);
    doParsimUnpacking(b,this->address);
    doParsimUnpacking(b,this->rewardValue);
    doParsimUnpacking(b,this->minQvalue2Destination);
    doParsimUnpacking(b,this->desinationAddressUDPdata);
}

const L3Address& QlHCACK::getAddress() const
{
    return this->address;
}

void QlHCACK::setAddress(const L3Address& address)
{
    handleChange();
    this->address = address;
}

double QlHCACK::getRewardValue() const
{
    return this->rewardValue;
}

void QlHCACK::setRewardValue(double rewardValue)
{
    handleChange();
    this->rewardValue = rewardValue;
}

double QlHCACK::getMinQvalue2Destination() const
{
    return this->minQvalue2Destination;
}

void QlHCACK::setMinQvalue2Destination(double minQvalue2Destination)
{
    handleChange();
    this->minQvalue2Destination = minQvalue2Destination;
}

const L3Address& QlHCACK::getDesinationAddressUDPdata() const
{
    return this->desinationAddressUDPdata;
}

void QlHCACK::setDesinationAddressUDPdata(const L3Address& desinationAddressUDPdata)
{
    handleChange();
    this->desinationAddressUDPdata = desinationAddressUDPdata;
}

class QlHCACKDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_address,
        FIELD_rewardValue,
        FIELD_minQvalue2Destination,
        FIELD_desinationAddressUDPdata,
    };
  public:
    QlHCACKDescriptor();
    virtual ~QlHCACKDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(QlHCACKDescriptor)

QlHCACKDescriptor::QlHCACKDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::QlHCACK)), "inet::FieldsChunk")
{
    propertyNames = nullptr;
}

QlHCACKDescriptor::~QlHCACKDescriptor()
{
    delete[] propertyNames;
}

bool QlHCACKDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<QlHCACK *>(obj)!=nullptr;
}

const char **QlHCACKDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *QlHCACKDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int QlHCACKDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 4+base->getFieldCount() : 4;
}

unsigned int QlHCACKDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        0,    // FIELD_address
        FD_ISEDITABLE,    // FIELD_rewardValue
        FD_ISEDITABLE,    // FIELD_minQvalue2Destination
        0,    // FIELD_desinationAddressUDPdata
    };
    return (field >= 0 && field < 4) ? fieldTypeFlags[field] : 0;
}

const char *QlHCACKDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "address",
        "rewardValue",
        "minQvalue2Destination",
        "desinationAddressUDPdata",
    };
    return (field >= 0 && field < 4) ? fieldNames[field] : nullptr;
}

int QlHCACKDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "address") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "rewardValue") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "minQvalue2Destination") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "desinationAddressUDPdata") == 0) return baseIndex + 3;
    return base ? base->findField(fieldName) : -1;
}

const char *QlHCACKDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::L3Address",    // FIELD_address
        "double",    // FIELD_rewardValue
        "double",    // FIELD_minQvalue2Destination
        "inet::L3Address",    // FIELD_desinationAddressUDPdata
    };
    return (field >= 0 && field < 4) ? fieldTypeStrings[field] : nullptr;
}

const char **QlHCACKDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *QlHCACKDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int QlHCACKDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    QlHCACK *pp = omnetpp::fromAnyPtr<QlHCACK>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void QlHCACKDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    QlHCACK *pp = omnetpp::fromAnyPtr<QlHCACK>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'QlHCACK'", field);
    }
}

const char *QlHCACKDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    QlHCACK *pp = omnetpp::fromAnyPtr<QlHCACK>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string QlHCACKDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    QlHCACK *pp = omnetpp::fromAnyPtr<QlHCACK>(object); (void)pp;
    switch (field) {
        case FIELD_address: return pp->getAddress().str();
        case FIELD_rewardValue: return double2string(pp->getRewardValue());
        case FIELD_minQvalue2Destination: return double2string(pp->getMinQvalue2Destination());
        case FIELD_desinationAddressUDPdata: return pp->getDesinationAddressUDPdata().str();
        default: return "";
    }
}

void QlHCACKDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    QlHCACK *pp = omnetpp::fromAnyPtr<QlHCACK>(object); (void)pp;
    switch (field) {
        case FIELD_rewardValue: pp->setRewardValue(string2double(value)); break;
        case FIELD_minQvalue2Destination: pp->setMinQvalue2Destination(string2double(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'QlHCACK'", field);
    }
}

omnetpp::cValue QlHCACKDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    QlHCACK *pp = omnetpp::fromAnyPtr<QlHCACK>(object); (void)pp;
    switch (field) {
        case FIELD_address: return omnetpp::toAnyPtr(&pp->getAddress()); break;
        case FIELD_rewardValue: return pp->getRewardValue();
        case FIELD_minQvalue2Destination: return pp->getMinQvalue2Destination();
        case FIELD_desinationAddressUDPdata: return omnetpp::toAnyPtr(&pp->getDesinationAddressUDPdata()); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'QlHCACK' as cValue -- field index out of range?", field);
    }
}

void QlHCACKDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    QlHCACK *pp = omnetpp::fromAnyPtr<QlHCACK>(object); (void)pp;
    switch (field) {
        case FIELD_rewardValue: pp->setRewardValue(value.doubleValue()); break;
        case FIELD_minQvalue2Destination: pp->setMinQvalue2Destination(value.doubleValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'QlHCACK'", field);
    }
}

const char *QlHCACKDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr QlHCACKDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    QlHCACK *pp = omnetpp::fromAnyPtr<QlHCACK>(object); (void)pp;
    switch (field) {
        case FIELD_address: return omnetpp::toAnyPtr(&pp->getAddress()); break;
        case FIELD_desinationAddressUDPdata: return omnetpp::toAnyPtr(&pp->getDesinationAddressUDPdata()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void QlHCACKDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    QlHCACK *pp = omnetpp::fromAnyPtr<QlHCACK>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'QlHCACK'", field);
    }
}

Register_Class(QlHCOption)

QlHCOption::QlHCOption() : ::inet::TlvOptionBase()
{
}

QlHCOption::QlHCOption(const QlHCOption& other) : ::inet::TlvOptionBase(other)
{
    copy(other);
}

QlHCOption::~QlHCOption()
{
}

QlHCOption& QlHCOption::operator=(const QlHCOption& other)
{
    if (this == &other) return *this;
    ::inet::TlvOptionBase::operator=(other);
    copy(other);
    return *this;
}

void QlHCOption::copy(const QlHCOption& other)
{
    this->routingMode = other.routingMode;
    this->destinationPosition = other.destinationPosition;
    this->perimeterRoutingStartPosition = other.perimeterRoutingStartPosition;
    this->perimeterRoutingForwardPosition = other.perimeterRoutingForwardPosition;
    this->currentFaceFirstSenderAddress = other.currentFaceFirstSenderAddress;
    this->currentFaceFirstReceiverAddress = other.currentFaceFirstReceiverAddress;
    this->senderAddress = other.senderAddress;
}

void QlHCOption::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::TlvOptionBase::parsimPack(b);
    doParsimPacking(b,this->routingMode);
    doParsimPacking(b,this->destinationPosition);
    doParsimPacking(b,this->perimeterRoutingStartPosition);
    doParsimPacking(b,this->perimeterRoutingForwardPosition);
    doParsimPacking(b,this->currentFaceFirstSenderAddress);
    doParsimPacking(b,this->currentFaceFirstReceiverAddress);
    doParsimPacking(b,this->senderAddress);
}

void QlHCOption::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::TlvOptionBase::parsimUnpack(b);
    doParsimUnpacking(b,this->routingMode);
    doParsimUnpacking(b,this->destinationPosition);
    doParsimUnpacking(b,this->perimeterRoutingStartPosition);
    doParsimUnpacking(b,this->perimeterRoutingForwardPosition);
    doParsimUnpacking(b,this->currentFaceFirstSenderAddress);
    doParsimUnpacking(b,this->currentFaceFirstReceiverAddress);
    doParsimUnpacking(b,this->senderAddress);
}

GpsrForwardingMode QlHCOption::getRoutingMode() const
{
    return this->routingMode;
}

void QlHCOption::setRoutingMode(GpsrForwardingMode routingMode)
{
    this->routingMode = routingMode;
}

const Coord& QlHCOption::getDestinationPosition() const
{
    return this->destinationPosition;
}

void QlHCOption::setDestinationPosition(const Coord& destinationPosition)
{
    this->destinationPosition = destinationPosition;
}

const Coord& QlHCOption::getPerimeterRoutingStartPosition() const
{
    return this->perimeterRoutingStartPosition;
}

void QlHCOption::setPerimeterRoutingStartPosition(const Coord& perimeterRoutingStartPosition)
{
    this->perimeterRoutingStartPosition = perimeterRoutingStartPosition;
}

const Coord& QlHCOption::getPerimeterRoutingForwardPosition() const
{
    return this->perimeterRoutingForwardPosition;
}

void QlHCOption::setPerimeterRoutingForwardPosition(const Coord& perimeterRoutingForwardPosition)
{
    this->perimeterRoutingForwardPosition = perimeterRoutingForwardPosition;
}

const L3Address& QlHCOption::getCurrentFaceFirstSenderAddress() const
{
    return this->currentFaceFirstSenderAddress;
}

void QlHCOption::setCurrentFaceFirstSenderAddress(const L3Address& currentFaceFirstSenderAddress)
{
    this->currentFaceFirstSenderAddress = currentFaceFirstSenderAddress;
}

const L3Address& QlHCOption::getCurrentFaceFirstReceiverAddress() const
{
    return this->currentFaceFirstReceiverAddress;
}

void QlHCOption::setCurrentFaceFirstReceiverAddress(const L3Address& currentFaceFirstReceiverAddress)
{
    this->currentFaceFirstReceiverAddress = currentFaceFirstReceiverAddress;
}

const L3Address& QlHCOption::getSenderAddress() const
{
    return this->senderAddress;
}

void QlHCOption::setSenderAddress(const L3Address& senderAddress)
{
    this->senderAddress = senderAddress;
}

class QlHCOptionDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_routingMode,
        FIELD_destinationPosition,
        FIELD_perimeterRoutingStartPosition,
        FIELD_perimeterRoutingForwardPosition,
        FIELD_currentFaceFirstSenderAddress,
        FIELD_currentFaceFirstReceiverAddress,
        FIELD_senderAddress,
    };
  public:
    QlHCOptionDescriptor();
    virtual ~QlHCOptionDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(QlHCOptionDescriptor)

QlHCOptionDescriptor::QlHCOptionDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::QlHCOption)), "inet::TlvOptionBase")
{
    propertyNames = nullptr;
}

QlHCOptionDescriptor::~QlHCOptionDescriptor()
{
    delete[] propertyNames;
}

bool QlHCOptionDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<QlHCOption *>(obj)!=nullptr;
}

const char **QlHCOptionDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *QlHCOptionDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int QlHCOptionDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 7+base->getFieldCount() : 7;
}

unsigned int QlHCOptionDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        0,    // FIELD_routingMode
        FD_ISCOMPOUND,    // FIELD_destinationPosition
        FD_ISCOMPOUND,    // FIELD_perimeterRoutingStartPosition
        FD_ISCOMPOUND,    // FIELD_perimeterRoutingForwardPosition
        0,    // FIELD_currentFaceFirstSenderAddress
        0,    // FIELD_currentFaceFirstReceiverAddress
        0,    // FIELD_senderAddress
    };
    return (field >= 0 && field < 7) ? fieldTypeFlags[field] : 0;
}

const char *QlHCOptionDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "routingMode",
        "destinationPosition",
        "perimeterRoutingStartPosition",
        "perimeterRoutingForwardPosition",
        "currentFaceFirstSenderAddress",
        "currentFaceFirstReceiverAddress",
        "senderAddress",
    };
    return (field >= 0 && field < 7) ? fieldNames[field] : nullptr;
}

int QlHCOptionDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "routingMode") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "destinationPosition") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "perimeterRoutingStartPosition") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "perimeterRoutingForwardPosition") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "currentFaceFirstSenderAddress") == 0) return baseIndex + 4;
    if (strcmp(fieldName, "currentFaceFirstReceiverAddress") == 0) return baseIndex + 5;
    if (strcmp(fieldName, "senderAddress") == 0) return baseIndex + 6;
    return base ? base->findField(fieldName) : -1;
}

const char *QlHCOptionDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::GpsrForwardingMode",    // FIELD_routingMode
        "inet::Coord",    // FIELD_destinationPosition
        "inet::Coord",    // FIELD_perimeterRoutingStartPosition
        "inet::Coord",    // FIELD_perimeterRoutingForwardPosition
        "inet::L3Address",    // FIELD_currentFaceFirstSenderAddress
        "inet::L3Address",    // FIELD_currentFaceFirstReceiverAddress
        "inet::L3Address",    // FIELD_senderAddress
    };
    return (field >= 0 && field < 7) ? fieldTypeStrings[field] : nullptr;
}

const char **QlHCOptionDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_routingMode: {
            static const char *names[] = { "enum",  nullptr };
            return names;
        }
        default: return nullptr;
    }
}

const char *QlHCOptionDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_routingMode:
            if (!strcmp(propertyName, "enum")) return "inet::GpsrForwardingMode";
            return nullptr;
        default: return nullptr;
    }
}

int QlHCOptionDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    QlHCOption *pp = omnetpp::fromAnyPtr<QlHCOption>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void QlHCOptionDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    QlHCOption *pp = omnetpp::fromAnyPtr<QlHCOption>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'QlHCOption'", field);
    }
}

const char *QlHCOptionDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    QlHCOption *pp = omnetpp::fromAnyPtr<QlHCOption>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string QlHCOptionDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    QlHCOption *pp = omnetpp::fromAnyPtr<QlHCOption>(object); (void)pp;
    switch (field) {
        case FIELD_routingMode: return enum2string(pp->getRoutingMode(), "inet::GpsrForwardingMode");
        case FIELD_destinationPosition: return "";
        case FIELD_perimeterRoutingStartPosition: return "";
        case FIELD_perimeterRoutingForwardPosition: return "";
        case FIELD_currentFaceFirstSenderAddress: return pp->getCurrentFaceFirstSenderAddress().str();
        case FIELD_currentFaceFirstReceiverAddress: return pp->getCurrentFaceFirstReceiverAddress().str();
        case FIELD_senderAddress: return pp->getSenderAddress().str();
        default: return "";
    }
}

void QlHCOptionDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    QlHCOption *pp = omnetpp::fromAnyPtr<QlHCOption>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'QlHCOption'", field);
    }
}

omnetpp::cValue QlHCOptionDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    QlHCOption *pp = omnetpp::fromAnyPtr<QlHCOption>(object); (void)pp;
    switch (field) {
        case FIELD_routingMode: return static_cast<int>(pp->getRoutingMode());
        case FIELD_destinationPosition: return omnetpp::toAnyPtr(&pp->getDestinationPosition()); break;
        case FIELD_perimeterRoutingStartPosition: return omnetpp::toAnyPtr(&pp->getPerimeterRoutingStartPosition()); break;
        case FIELD_perimeterRoutingForwardPosition: return omnetpp::toAnyPtr(&pp->getPerimeterRoutingForwardPosition()); break;
        case FIELD_currentFaceFirstSenderAddress: return omnetpp::toAnyPtr(&pp->getCurrentFaceFirstSenderAddress()); break;
        case FIELD_currentFaceFirstReceiverAddress: return omnetpp::toAnyPtr(&pp->getCurrentFaceFirstReceiverAddress()); break;
        case FIELD_senderAddress: return omnetpp::toAnyPtr(&pp->getSenderAddress()); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'QlHCOption' as cValue -- field index out of range?", field);
    }
}

void QlHCOptionDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    QlHCOption *pp = omnetpp::fromAnyPtr<QlHCOption>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'QlHCOption'", field);
    }
}

const char *QlHCOptionDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_destinationPosition: return omnetpp::opp_typename(typeid(Coord));
        case FIELD_perimeterRoutingStartPosition: return omnetpp::opp_typename(typeid(Coord));
        case FIELD_perimeterRoutingForwardPosition: return omnetpp::opp_typename(typeid(Coord));
        default: return nullptr;
    };
}

omnetpp::any_ptr QlHCOptionDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    QlHCOption *pp = omnetpp::fromAnyPtr<QlHCOption>(object); (void)pp;
    switch (field) {
        case FIELD_destinationPosition: return omnetpp::toAnyPtr(&pp->getDestinationPosition()); break;
        case FIELD_perimeterRoutingStartPosition: return omnetpp::toAnyPtr(&pp->getPerimeterRoutingStartPosition()); break;
        case FIELD_perimeterRoutingForwardPosition: return omnetpp::toAnyPtr(&pp->getPerimeterRoutingForwardPosition()); break;
        case FIELD_currentFaceFirstSenderAddress: return omnetpp::toAnyPtr(&pp->getCurrentFaceFirstSenderAddress()); break;
        case FIELD_currentFaceFirstReceiverAddress: return omnetpp::toAnyPtr(&pp->getCurrentFaceFirstReceiverAddress()); break;
        case FIELD_senderAddress: return omnetpp::toAnyPtr(&pp->getSenderAddress()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void QlHCOptionDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    QlHCOption *pp = omnetpp::fromAnyPtr<QlHCOption>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'QlHCOption'", field);
    }
}

}  // namespace inet

namespace omnetpp {

}  // namespace omnetpp

