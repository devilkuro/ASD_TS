//
// Generated file, do not edit! Created by opp_msgc 4.1 from overlay/ASD_TS/ATSOverlay.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "ATSOverlay_m.h"

// Template rule which fires if a struct or class doesn't have operator<<
template<typename T>
std::ostream& operator<<(std::ostream& out,const T&) {return out;}

// Another default rule (prevents compiler from choosing base class' doPacking())
template<typename T>
void doPacking(cCommBuffer *, T& t) {
    throw cRuntimeError("Parsim error: no doPacking() function for type %s or its base class (check .msg and _m.cc/h files!)",opp_typename(typeid(t)));
}

template<typename T>
void doUnpacking(cCommBuffer *, T& t) {
    throw cRuntimeError("Parsim error: no doUnpacking() function for type %s or its base class (check .msg and _m.cc/h files!)",opp_typename(typeid(t)));
}




EXECUTE_ON_STARTUP(
    cEnum *e = cEnum::find("ATSCommand");
    if (!e) enums.getInstance()->add(e = new cEnum("ATSCommand"));
    e->insert(ATS_NULL, "ATS_NULL");
    e->insert(ATS_QUERY, "ATS_QUERY");
    e->insert(ATS_QUERY_RESPONSE, "ATS_QUERY_RESPONSE");
    e->insert(ATS_JOINEVAL, "ATS_JOINEVAL");
    e->insert(ATS_JOINEVAL_RESPONSE, "ATS_JOINEVAL_RESPONSE");
    e->insert(ATS_JOIN, "ATS_JOIN");
    e->insert(ATS_JOIN_RESPONSE, "ATS_JOIN_RESPONSE");
    e->insert(ATS_INSERT, "ATS_INSERT");
    e->insert(ATS_INSERT_RESPONSE, "ATS_INSERT_RESPONSE");
    e->insert(ATS_JOIN_SUCCESS, "ATS_JOIN_SUCCESS");
    e->insert(ATS_STATISTIC, "ATS_STATISTIC");
);

Register_Class(ATSMessage);

ATSMessage::ATSMessage(const char *name, int kind) : BaseOverlayMessage(name,kind)
{
    this->command_var = ATS_NULL;
    this->sendTime_var = 0;
}

ATSMessage::ATSMessage(const ATSMessage& other) : BaseOverlayMessage()
{
    setName(other.getName());
    operator=(other);
}

ATSMessage::~ATSMessage()
{
}

ATSMessage& ATSMessage::operator=(const ATSMessage& other)
{
    if (this==&other) return *this;
    BaseOverlayMessage::operator=(other);
    this->command_var = other.command_var;
    this->sourceAddress_var = other.sourceAddress_var;
    this->sendTime_var = other.sendTime_var;
    return *this;
}

void ATSMessage::parsimPack(cCommBuffer *b)
{
    BaseOverlayMessage::parsimPack(b);
    doPacking(b,this->command_var);
    doPacking(b,this->sourceAddress_var);
    doPacking(b,this->sendTime_var);
}

void ATSMessage::parsimUnpack(cCommBuffer *b)
{
    BaseOverlayMessage::parsimUnpack(b);
    doUnpacking(b,this->command_var);
    doUnpacking(b,this->sourceAddress_var);
    doUnpacking(b,this->sendTime_var);
}

int ATSMessage::getCommand() const
{
    return command_var;
}

void ATSMessage::setCommand(int command_var)
{
    this->command_var = command_var;
}

TransportAddress& ATSMessage::getSourceAddress()
{
    return sourceAddress_var;
}

void ATSMessage::setSourceAddress(const TransportAddress& sourceAddress_var)
{
    this->sourceAddress_var = sourceAddress_var;
}

double ATSMessage::getSendTime() const
{
    return sendTime_var;
}

void ATSMessage::setSendTime(double sendTime_var)
{
    this->sendTime_var = sendTime_var;
}

class ATSMessageDescriptor : public cClassDescriptor
{
  public:
    ATSMessageDescriptor();
    virtual ~ATSMessageDescriptor();

    virtual bool doesSupport(cObject *obj) const;
    virtual const char *getProperty(const char *propertyname) const;
    virtual int getFieldCount(void *object) const;
    virtual const char *getFieldName(void *object, int field) const;
    virtual int findField(void *object, const char *fieldName) const;
    virtual unsigned int getFieldTypeFlags(void *object, int field) const;
    virtual const char *getFieldTypeString(void *object, int field) const;
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname) const;
    virtual int getArraySize(void *object, int field) const;

    virtual std::string getFieldAsString(void *object, int field, int i) const;
    virtual bool setFieldAsString(void *object, int field, int i, const char *value) const;

    virtual const char *getFieldStructName(void *object, int field) const;
    virtual void *getFieldStructPointer(void *object, int field, int i) const;
};

Register_ClassDescriptor(ATSMessageDescriptor);

ATSMessageDescriptor::ATSMessageDescriptor() : cClassDescriptor("ATSMessage", "BaseOverlayMessage")
{
}

ATSMessageDescriptor::~ATSMessageDescriptor()
{
}

bool ATSMessageDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<ATSMessage *>(obj)!=NULL;
}

const char *ATSMessageDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int ATSMessageDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 3+basedesc->getFieldCount(object) : 3;
}

unsigned int ATSMessageDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISCOMPOUND,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<3) ? fieldTypeFlags[field] : 0;
}

const char *ATSMessageDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "command",
        "sourceAddress",
        "sendTime",
    };
    return (field>=0 && field<3) ? fieldNames[field] : NULL;
}

int ATSMessageDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='c' && strcmp(fieldName, "command")==0) return base+0;
    if (fieldName[0]=='s' && strcmp(fieldName, "sourceAddress")==0) return base+1;
    if (fieldName[0]=='s' && strcmp(fieldName, "sendTime")==0) return base+2;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *ATSMessageDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "int",
        "TransportAddress",
        "double",
    };
    return (field>=0 && field<3) ? fieldTypeStrings[field] : NULL;
}

const char *ATSMessageDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0:
            if (!strcmp(propertyname,"enum")) return "ATSCommand";
            return NULL;
        default: return NULL;
    }
}

int ATSMessageDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    ATSMessage *pp = (ATSMessage *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string ATSMessageDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    ATSMessage *pp = (ATSMessage *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getCommand());
        case 1: {std::stringstream out; out << pp->getSourceAddress(); return out.str();}
        case 2: return double2string(pp->getSendTime());
        default: return "";
    }
}

bool ATSMessageDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    ATSMessage *pp = (ATSMessage *)object; (void)pp;
    switch (field) {
        case 0: pp->setCommand(string2long(value)); return true;
        case 2: pp->setSendTime(string2double(value)); return true;
        default: return false;
    }
}

const char *ATSMessageDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldStructNames[] = {
        NULL,
        "TransportAddress",
        NULL,
    };
    return (field>=0 && field<3) ? fieldStructNames[field] : NULL;
}

void *ATSMessageDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    ATSMessage *pp = (ATSMessage *)object; (void)pp;
    switch (field) {
        case 1: return (void *)(&pp->getSourceAddress()); break;
        default: return NULL;
    }
}

Register_Class(ATSQueryMessage);

ATSQueryMessage::ATSQueryMessage(const char *name, int kind) : ATSMessage(name,kind)
{
    this->setCommand(ATS_QUERY);
}

ATSQueryMessage::ATSQueryMessage(const ATSQueryMessage& other) : ATSMessage()
{
    setName(other.getName());
    operator=(other);
}

ATSQueryMessage::~ATSQueryMessage()
{
}

ATSQueryMessage& ATSQueryMessage::operator=(const ATSQueryMessage& other)
{
    if (this==&other) return *this;
    ATSMessage::operator=(other);
    return *this;
}

void ATSQueryMessage::parsimPack(cCommBuffer *b)
{
    ATSMessage::parsimPack(b);
}

void ATSQueryMessage::parsimUnpack(cCommBuffer *b)
{
    ATSMessage::parsimUnpack(b);
}

class ATSQueryMessageDescriptor : public cClassDescriptor
{
  public:
    ATSQueryMessageDescriptor();
    virtual ~ATSQueryMessageDescriptor();

    virtual bool doesSupport(cObject *obj) const;
    virtual const char *getProperty(const char *propertyname) const;
    virtual int getFieldCount(void *object) const;
    virtual const char *getFieldName(void *object, int field) const;
    virtual int findField(void *object, const char *fieldName) const;
    virtual unsigned int getFieldTypeFlags(void *object, int field) const;
    virtual const char *getFieldTypeString(void *object, int field) const;
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname) const;
    virtual int getArraySize(void *object, int field) const;

    virtual std::string getFieldAsString(void *object, int field, int i) const;
    virtual bool setFieldAsString(void *object, int field, int i, const char *value) const;

    virtual const char *getFieldStructName(void *object, int field) const;
    virtual void *getFieldStructPointer(void *object, int field, int i) const;
};

Register_ClassDescriptor(ATSQueryMessageDescriptor);

ATSQueryMessageDescriptor::ATSQueryMessageDescriptor() : cClassDescriptor("ATSQueryMessage", "ATSMessage")
{
}

ATSQueryMessageDescriptor::~ATSQueryMessageDescriptor()
{
}

bool ATSQueryMessageDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<ATSQueryMessage *>(obj)!=NULL;
}

const char *ATSQueryMessageDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int ATSQueryMessageDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 0+basedesc->getFieldCount(object) : 0;
}

unsigned int ATSQueryMessageDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    return 0;
}

const char *ATSQueryMessageDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    return NULL;
}

int ATSQueryMessageDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *ATSQueryMessageDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    return NULL;
}

const char *ATSQueryMessageDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int ATSQueryMessageDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    ATSQueryMessage *pp = (ATSQueryMessage *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string ATSQueryMessageDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    ATSQueryMessage *pp = (ATSQueryMessage *)object; (void)pp;
    switch (field) {
        default: return "";
    }
}

bool ATSQueryMessageDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    ATSQueryMessage *pp = (ATSQueryMessage *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *ATSQueryMessageDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    return NULL;
}

void *ATSQueryMessageDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    ATSQueryMessage *pp = (ATSQueryMessage *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(ATSQueryResponseMessage);

ATSQueryResponseMessage::ATSQueryResponseMessage(const char *name, int kind) : ATSMessage(name,kind)
{
    this->setCommand(ATS_QUERY_RESPONSE);

    memberAddress_arraysize = 0;
    this->memberAddress_var = 0;
    this->freeDegree_var = 0;
}

ATSQueryResponseMessage::ATSQueryResponseMessage(const ATSQueryResponseMessage& other) : ATSMessage()
{
    setName(other.getName());
    memberAddress_arraysize = 0;
    this->memberAddress_var = 0;
    operator=(other);
}

ATSQueryResponseMessage::~ATSQueryResponseMessage()
{
    delete [] memberAddress_var;
}

ATSQueryResponseMessage& ATSQueryResponseMessage::operator=(const ATSQueryResponseMessage& other)
{
    if (this==&other) return *this;
    ATSMessage::operator=(other);
    delete [] this->memberAddress_var;
    this->memberAddress_var = (other.memberAddress_arraysize==0) ? NULL : new ::TransportAddress[other.memberAddress_arraysize];
    memberAddress_arraysize = other.memberAddress_arraysize;
    for (unsigned int i=0; i<memberAddress_arraysize; i++)
        this->memberAddress_var[i] = other.memberAddress_var[i];
    this->freeDegree_var = other.freeDegree_var;
    return *this;
}

void ATSQueryResponseMessage::parsimPack(cCommBuffer *b)
{
    ATSMessage::parsimPack(b);
    b->pack(memberAddress_arraysize);
    doPacking(b,this->memberAddress_var,memberAddress_arraysize);
    doPacking(b,this->freeDegree_var);
}

void ATSQueryResponseMessage::parsimUnpack(cCommBuffer *b)
{
    ATSMessage::parsimUnpack(b);
    delete [] this->memberAddress_var;
    b->unpack(memberAddress_arraysize);
    if (memberAddress_arraysize==0) {
        this->memberAddress_var = 0;
    } else {
        this->memberAddress_var = new ::TransportAddress[memberAddress_arraysize];
        doUnpacking(b,this->memberAddress_var,memberAddress_arraysize);
    }
    doUnpacking(b,this->freeDegree_var);
}

void ATSQueryResponseMessage::setMemberAddressArraySize(unsigned int size)
{
    ::TransportAddress *memberAddress_var2 = (size==0) ? NULL : new ::TransportAddress[size];
    unsigned int sz = memberAddress_arraysize < size ? memberAddress_arraysize : size;
    for (unsigned int i=0; i<sz; i++)
        memberAddress_var2[i] = this->memberAddress_var[i];
    memberAddress_arraysize = size;
    delete [] this->memberAddress_var;
    this->memberAddress_var = memberAddress_var2;
}

unsigned int ATSQueryResponseMessage::getMemberAddressArraySize() const
{
    return memberAddress_arraysize;
}

TransportAddress& ATSQueryResponseMessage::getMemberAddress(unsigned int k)
{
    if (k>=memberAddress_arraysize) throw cRuntimeError("Array of size %d indexed by %d", memberAddress_arraysize, k);
    return memberAddress_var[k];
}

void ATSQueryResponseMessage::setMemberAddress(unsigned int k, const TransportAddress& memberAddress_var)
{
    if (k>=memberAddress_arraysize) throw cRuntimeError("Array of size %d indexed by %d", memberAddress_arraysize, k);
    this->memberAddress_var[k]=memberAddress_var;
}

unsigned int ATSQueryResponseMessage::getFreeDegree() const
{
    return freeDegree_var;
}

void ATSQueryResponseMessage::setFreeDegree(unsigned int freeDegree_var)
{
    this->freeDegree_var = freeDegree_var;
}

class ATSQueryResponseMessageDescriptor : public cClassDescriptor
{
  public:
    ATSQueryResponseMessageDescriptor();
    virtual ~ATSQueryResponseMessageDescriptor();

    virtual bool doesSupport(cObject *obj) const;
    virtual const char *getProperty(const char *propertyname) const;
    virtual int getFieldCount(void *object) const;
    virtual const char *getFieldName(void *object, int field) const;
    virtual int findField(void *object, const char *fieldName) const;
    virtual unsigned int getFieldTypeFlags(void *object, int field) const;
    virtual const char *getFieldTypeString(void *object, int field) const;
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname) const;
    virtual int getArraySize(void *object, int field) const;

    virtual std::string getFieldAsString(void *object, int field, int i) const;
    virtual bool setFieldAsString(void *object, int field, int i, const char *value) const;

    virtual const char *getFieldStructName(void *object, int field) const;
    virtual void *getFieldStructPointer(void *object, int field, int i) const;
};

Register_ClassDescriptor(ATSQueryResponseMessageDescriptor);

ATSQueryResponseMessageDescriptor::ATSQueryResponseMessageDescriptor() : cClassDescriptor("ATSQueryResponseMessage", "ATSMessage")
{
}

ATSQueryResponseMessageDescriptor::~ATSQueryResponseMessageDescriptor()
{
}

bool ATSQueryResponseMessageDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<ATSQueryResponseMessage *>(obj)!=NULL;
}

const char *ATSQueryResponseMessageDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int ATSQueryResponseMessageDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 2+basedesc->getFieldCount(object) : 2;
}

unsigned int ATSQueryResponseMessageDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISARRAY | FD_ISCOMPOUND,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<2) ? fieldTypeFlags[field] : 0;
}

const char *ATSQueryResponseMessageDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "memberAddress",
        "freeDegree",
    };
    return (field>=0 && field<2) ? fieldNames[field] : NULL;
}

int ATSQueryResponseMessageDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='m' && strcmp(fieldName, "memberAddress")==0) return base+0;
    if (fieldName[0]=='f' && strcmp(fieldName, "freeDegree")==0) return base+1;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *ATSQueryResponseMessageDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "TransportAddress",
        "unsigned int",
    };
    return (field>=0 && field<2) ? fieldTypeStrings[field] : NULL;
}

const char *ATSQueryResponseMessageDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int ATSQueryResponseMessageDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    ATSQueryResponseMessage *pp = (ATSQueryResponseMessage *)object; (void)pp;
    switch (field) {
        case 0: return pp->getMemberAddressArraySize();
        default: return 0;
    }
}

std::string ATSQueryResponseMessageDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    ATSQueryResponseMessage *pp = (ATSQueryResponseMessage *)object; (void)pp;
    switch (field) {
        case 0: {std::stringstream out; out << pp->getMemberAddress(i); return out.str();}
        case 1: return ulong2string(pp->getFreeDegree());
        default: return "";
    }
}

bool ATSQueryResponseMessageDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    ATSQueryResponseMessage *pp = (ATSQueryResponseMessage *)object; (void)pp;
    switch (field) {
        case 1: pp->setFreeDegree(string2ulong(value)); return true;
        default: return false;
    }
}

const char *ATSQueryResponseMessageDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldStructNames[] = {
        "TransportAddress",
        NULL,
    };
    return (field>=0 && field<2) ? fieldStructNames[field] : NULL;
}

void *ATSQueryResponseMessageDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    ATSQueryResponseMessage *pp = (ATSQueryResponseMessage *)object; (void)pp;
    switch (field) {
        case 0: return (void *)(&pp->getMemberAddress(i)); break;
        default: return NULL;
    }
}

Register_Class(ATSJoinEvalMessage);

ATSJoinEvalMessage::ATSJoinEvalMessage(const char *name, int kind) : ATSMessage(name,kind)
{
    this->setCommand(ATS_JOINEVAL);
}

ATSJoinEvalMessage::ATSJoinEvalMessage(const ATSJoinEvalMessage& other) : ATSMessage()
{
    setName(other.getName());
    operator=(other);
}

ATSJoinEvalMessage::~ATSJoinEvalMessage()
{
}

ATSJoinEvalMessage& ATSJoinEvalMessage::operator=(const ATSJoinEvalMessage& other)
{
    if (this==&other) return *this;
    ATSMessage::operator=(other);
    return *this;
}

void ATSJoinEvalMessage::parsimPack(cCommBuffer *b)
{
    ATSMessage::parsimPack(b);
}

void ATSJoinEvalMessage::parsimUnpack(cCommBuffer *b)
{
    ATSMessage::parsimUnpack(b);
}

class ATSJoinEvalMessageDescriptor : public cClassDescriptor
{
  public:
    ATSJoinEvalMessageDescriptor();
    virtual ~ATSJoinEvalMessageDescriptor();

    virtual bool doesSupport(cObject *obj) const;
    virtual const char *getProperty(const char *propertyname) const;
    virtual int getFieldCount(void *object) const;
    virtual const char *getFieldName(void *object, int field) const;
    virtual int findField(void *object, const char *fieldName) const;
    virtual unsigned int getFieldTypeFlags(void *object, int field) const;
    virtual const char *getFieldTypeString(void *object, int field) const;
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname) const;
    virtual int getArraySize(void *object, int field) const;

    virtual std::string getFieldAsString(void *object, int field, int i) const;
    virtual bool setFieldAsString(void *object, int field, int i, const char *value) const;

    virtual const char *getFieldStructName(void *object, int field) const;
    virtual void *getFieldStructPointer(void *object, int field, int i) const;
};

Register_ClassDescriptor(ATSJoinEvalMessageDescriptor);

ATSJoinEvalMessageDescriptor::ATSJoinEvalMessageDescriptor() : cClassDescriptor("ATSJoinEvalMessage", "ATSMessage")
{
}

ATSJoinEvalMessageDescriptor::~ATSJoinEvalMessageDescriptor()
{
}

bool ATSJoinEvalMessageDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<ATSJoinEvalMessage *>(obj)!=NULL;
}

const char *ATSJoinEvalMessageDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int ATSJoinEvalMessageDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 0+basedesc->getFieldCount(object) : 0;
}

unsigned int ATSJoinEvalMessageDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    return 0;
}

const char *ATSJoinEvalMessageDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    return NULL;
}

int ATSJoinEvalMessageDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *ATSJoinEvalMessageDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    return NULL;
}

const char *ATSJoinEvalMessageDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int ATSJoinEvalMessageDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    ATSJoinEvalMessage *pp = (ATSJoinEvalMessage *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string ATSJoinEvalMessageDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    ATSJoinEvalMessage *pp = (ATSJoinEvalMessage *)object; (void)pp;
    switch (field) {
        default: return "";
    }
}

bool ATSJoinEvalMessageDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    ATSJoinEvalMessage *pp = (ATSJoinEvalMessage *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *ATSJoinEvalMessageDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    return NULL;
}

void *ATSJoinEvalMessageDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    ATSJoinEvalMessage *pp = (ATSJoinEvalMessage *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(ATSJoinEvalResponseMessage);

ATSJoinEvalResponseMessage::ATSJoinEvalResponseMessage(const char *name, int kind) : ATSMessage(name,kind)
{
    this->setCommand(ATS_JOINEVAL_RESPONSE);

    this->freeDegree_var = 0;
    dataTimeStamp_arraysize = 0;
    this->dataTimeStamp_var = 0;
    parentAddress_arraysize = 0;
    this->parentAddress_var = 0;
    childAddress_arraysize = 0;
    this->childAddress_var = 0;
    childDataSeq_arraysize = 0;
    this->childDataSeq_var = 0;
}

ATSJoinEvalResponseMessage::ATSJoinEvalResponseMessage(const ATSJoinEvalResponseMessage& other) : ATSMessage()
{
    setName(other.getName());
    dataTimeStamp_arraysize = 0;
    this->dataTimeStamp_var = 0;
    parentAddress_arraysize = 0;
    this->parentAddress_var = 0;
    childAddress_arraysize = 0;
    this->childAddress_var = 0;
    childDataSeq_arraysize = 0;
    this->childDataSeq_var = 0;
    operator=(other);
}

ATSJoinEvalResponseMessage::~ATSJoinEvalResponseMessage()
{
    delete [] dataTimeStamp_var;
    delete [] parentAddress_var;
    delete [] childAddress_var;
    delete [] childDataSeq_var;
}

ATSJoinEvalResponseMessage& ATSJoinEvalResponseMessage::operator=(const ATSJoinEvalResponseMessage& other)
{
    if (this==&other) return *this;
    ATSMessage::operator=(other);
    this->freeDegree_var = other.freeDegree_var;
    delete [] this->dataTimeStamp_var;
    this->dataTimeStamp_var = (other.dataTimeStamp_arraysize==0) ? NULL : new double[other.dataTimeStamp_arraysize];
    dataTimeStamp_arraysize = other.dataTimeStamp_arraysize;
    for (unsigned int i=0; i<dataTimeStamp_arraysize; i++)
        this->dataTimeStamp_var[i] = other.dataTimeStamp_var[i];
    delete [] this->parentAddress_var;
    this->parentAddress_var = (other.parentAddress_arraysize==0) ? NULL : new ::TransportAddress[other.parentAddress_arraysize];
    parentAddress_arraysize = other.parentAddress_arraysize;
    for (unsigned int i=0; i<parentAddress_arraysize; i++)
        this->parentAddress_var[i] = other.parentAddress_var[i];
    delete [] this->childAddress_var;
    this->childAddress_var = (other.childAddress_arraysize==0) ? NULL : new ::TransportAddress[other.childAddress_arraysize];
    childAddress_arraysize = other.childAddress_arraysize;
    for (unsigned int i=0; i<childAddress_arraysize; i++)
        this->childAddress_var[i] = other.childAddress_var[i];
    delete [] this->childDataSeq_var;
    this->childDataSeq_var = (other.childDataSeq_arraysize==0) ? NULL : new unsigned int[other.childDataSeq_arraysize];
    childDataSeq_arraysize = other.childDataSeq_arraysize;
    for (unsigned int i=0; i<childDataSeq_arraysize; i++)
        this->childDataSeq_var[i] = other.childDataSeq_var[i];
    return *this;
}

void ATSJoinEvalResponseMessage::parsimPack(cCommBuffer *b)
{
    ATSMessage::parsimPack(b);
    doPacking(b,this->freeDegree_var);
    b->pack(dataTimeStamp_arraysize);
    doPacking(b,this->dataTimeStamp_var,dataTimeStamp_arraysize);
    b->pack(parentAddress_arraysize);
    doPacking(b,this->parentAddress_var,parentAddress_arraysize);
    b->pack(childAddress_arraysize);
    doPacking(b,this->childAddress_var,childAddress_arraysize);
    b->pack(childDataSeq_arraysize);
    doPacking(b,this->childDataSeq_var,childDataSeq_arraysize);
}

void ATSJoinEvalResponseMessage::parsimUnpack(cCommBuffer *b)
{
    ATSMessage::parsimUnpack(b);
    doUnpacking(b,this->freeDegree_var);
    delete [] this->dataTimeStamp_var;
    b->unpack(dataTimeStamp_arraysize);
    if (dataTimeStamp_arraysize==0) {
        this->dataTimeStamp_var = 0;
    } else {
        this->dataTimeStamp_var = new double[dataTimeStamp_arraysize];
        doUnpacking(b,this->dataTimeStamp_var,dataTimeStamp_arraysize);
    }
    delete [] this->parentAddress_var;
    b->unpack(parentAddress_arraysize);
    if (parentAddress_arraysize==0) {
        this->parentAddress_var = 0;
    } else {
        this->parentAddress_var = new ::TransportAddress[parentAddress_arraysize];
        doUnpacking(b,this->parentAddress_var,parentAddress_arraysize);
    }
    delete [] this->childAddress_var;
    b->unpack(childAddress_arraysize);
    if (childAddress_arraysize==0) {
        this->childAddress_var = 0;
    } else {
        this->childAddress_var = new ::TransportAddress[childAddress_arraysize];
        doUnpacking(b,this->childAddress_var,childAddress_arraysize);
    }
    delete [] this->childDataSeq_var;
    b->unpack(childDataSeq_arraysize);
    if (childDataSeq_arraysize==0) {
        this->childDataSeq_var = 0;
    } else {
        this->childDataSeq_var = new unsigned int[childDataSeq_arraysize];
        doUnpacking(b,this->childDataSeq_var,childDataSeq_arraysize);
    }
}

unsigned int ATSJoinEvalResponseMessage::getFreeDegree() const
{
    return freeDegree_var;
}

void ATSJoinEvalResponseMessage::setFreeDegree(unsigned int freeDegree_var)
{
    this->freeDegree_var = freeDegree_var;
}

void ATSJoinEvalResponseMessage::setDataTimeStampArraySize(unsigned int size)
{
    double *dataTimeStamp_var2 = (size==0) ? NULL : new double[size];
    unsigned int sz = dataTimeStamp_arraysize < size ? dataTimeStamp_arraysize : size;
    for (unsigned int i=0; i<sz; i++)
        dataTimeStamp_var2[i] = this->dataTimeStamp_var[i];
    for (unsigned int i=sz; i<size; i++)
        dataTimeStamp_var2[i] = 0;
    dataTimeStamp_arraysize = size;
    delete [] this->dataTimeStamp_var;
    this->dataTimeStamp_var = dataTimeStamp_var2;
}

unsigned int ATSJoinEvalResponseMessage::getDataTimeStampArraySize() const
{
    return dataTimeStamp_arraysize;
}

double ATSJoinEvalResponseMessage::getDataTimeStamp(unsigned int k) const
{
    if (k>=dataTimeStamp_arraysize) throw cRuntimeError("Array of size %d indexed by %d", dataTimeStamp_arraysize, k);
    return dataTimeStamp_var[k];
}

void ATSJoinEvalResponseMessage::setDataTimeStamp(unsigned int k, double dataTimeStamp_var)
{
    if (k>=dataTimeStamp_arraysize) throw cRuntimeError("Array of size %d indexed by %d", dataTimeStamp_arraysize, k);
    this->dataTimeStamp_var[k]=dataTimeStamp_var;
}

void ATSJoinEvalResponseMessage::setParentAddressArraySize(unsigned int size)
{
    ::TransportAddress *parentAddress_var2 = (size==0) ? NULL : new ::TransportAddress[size];
    unsigned int sz = parentAddress_arraysize < size ? parentAddress_arraysize : size;
    for (unsigned int i=0; i<sz; i++)
        parentAddress_var2[i] = this->parentAddress_var[i];
    parentAddress_arraysize = size;
    delete [] this->parentAddress_var;
    this->parentAddress_var = parentAddress_var2;
}

unsigned int ATSJoinEvalResponseMessage::getParentAddressArraySize() const
{
    return parentAddress_arraysize;
}

TransportAddress& ATSJoinEvalResponseMessage::getParentAddress(unsigned int k)
{
    if (k>=parentAddress_arraysize) throw cRuntimeError("Array of size %d indexed by %d", parentAddress_arraysize, k);
    return parentAddress_var[k];
}

void ATSJoinEvalResponseMessage::setParentAddress(unsigned int k, const TransportAddress& parentAddress_var)
{
    if (k>=parentAddress_arraysize) throw cRuntimeError("Array of size %d indexed by %d", parentAddress_arraysize, k);
    this->parentAddress_var[k]=parentAddress_var;
}

void ATSJoinEvalResponseMessage::setChildAddressArraySize(unsigned int size)
{
    ::TransportAddress *childAddress_var2 = (size==0) ? NULL : new ::TransportAddress[size];
    unsigned int sz = childAddress_arraysize < size ? childAddress_arraysize : size;
    for (unsigned int i=0; i<sz; i++)
        childAddress_var2[i] = this->childAddress_var[i];
    childAddress_arraysize = size;
    delete [] this->childAddress_var;
    this->childAddress_var = childAddress_var2;
}

unsigned int ATSJoinEvalResponseMessage::getChildAddressArraySize() const
{
    return childAddress_arraysize;
}

TransportAddress& ATSJoinEvalResponseMessage::getChildAddress(unsigned int k)
{
    if (k>=childAddress_arraysize) throw cRuntimeError("Array of size %d indexed by %d", childAddress_arraysize, k);
    return childAddress_var[k];
}

void ATSJoinEvalResponseMessage::setChildAddress(unsigned int k, const TransportAddress& childAddress_var)
{
    if (k>=childAddress_arraysize) throw cRuntimeError("Array of size %d indexed by %d", childAddress_arraysize, k);
    this->childAddress_var[k]=childAddress_var;
}

void ATSJoinEvalResponseMessage::setChildDataSeqArraySize(unsigned int size)
{
    unsigned int *childDataSeq_var2 = (size==0) ? NULL : new unsigned int[size];
    unsigned int sz = childDataSeq_arraysize < size ? childDataSeq_arraysize : size;
    for (unsigned int i=0; i<sz; i++)
        childDataSeq_var2[i] = this->childDataSeq_var[i];
    for (unsigned int i=sz; i<size; i++)
        childDataSeq_var2[i] = 0;
    childDataSeq_arraysize = size;
    delete [] this->childDataSeq_var;
    this->childDataSeq_var = childDataSeq_var2;
}

unsigned int ATSJoinEvalResponseMessage::getChildDataSeqArraySize() const
{
    return childDataSeq_arraysize;
}

unsigned int ATSJoinEvalResponseMessage::getChildDataSeq(unsigned int k) const
{
    if (k>=childDataSeq_arraysize) throw cRuntimeError("Array of size %d indexed by %d", childDataSeq_arraysize, k);
    return childDataSeq_var[k];
}

void ATSJoinEvalResponseMessage::setChildDataSeq(unsigned int k, unsigned int childDataSeq_var)
{
    if (k>=childDataSeq_arraysize) throw cRuntimeError("Array of size %d indexed by %d", childDataSeq_arraysize, k);
    this->childDataSeq_var[k]=childDataSeq_var;
}

class ATSJoinEvalResponseMessageDescriptor : public cClassDescriptor
{
  public:
    ATSJoinEvalResponseMessageDescriptor();
    virtual ~ATSJoinEvalResponseMessageDescriptor();

    virtual bool doesSupport(cObject *obj) const;
    virtual const char *getProperty(const char *propertyname) const;
    virtual int getFieldCount(void *object) const;
    virtual const char *getFieldName(void *object, int field) const;
    virtual int findField(void *object, const char *fieldName) const;
    virtual unsigned int getFieldTypeFlags(void *object, int field) const;
    virtual const char *getFieldTypeString(void *object, int field) const;
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname) const;
    virtual int getArraySize(void *object, int field) const;

    virtual std::string getFieldAsString(void *object, int field, int i) const;
    virtual bool setFieldAsString(void *object, int field, int i, const char *value) const;

    virtual const char *getFieldStructName(void *object, int field) const;
    virtual void *getFieldStructPointer(void *object, int field, int i) const;
};

Register_ClassDescriptor(ATSJoinEvalResponseMessageDescriptor);

ATSJoinEvalResponseMessageDescriptor::ATSJoinEvalResponseMessageDescriptor() : cClassDescriptor("ATSJoinEvalResponseMessage", "ATSMessage")
{
}

ATSJoinEvalResponseMessageDescriptor::~ATSJoinEvalResponseMessageDescriptor()
{
}

bool ATSJoinEvalResponseMessageDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<ATSJoinEvalResponseMessage *>(obj)!=NULL;
}

const char *ATSJoinEvalResponseMessageDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int ATSJoinEvalResponseMessageDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 5+basedesc->getFieldCount(object) : 5;
}

unsigned int ATSJoinEvalResponseMessageDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISARRAY | FD_ISEDITABLE,
        FD_ISARRAY | FD_ISCOMPOUND,
        FD_ISARRAY | FD_ISCOMPOUND,
        FD_ISARRAY | FD_ISEDITABLE,
    };
    return (field>=0 && field<5) ? fieldTypeFlags[field] : 0;
}

const char *ATSJoinEvalResponseMessageDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "freeDegree",
        "dataTimeStamp",
        "parentAddress",
        "childAddress",
        "childDataSeq",
    };
    return (field>=0 && field<5) ? fieldNames[field] : NULL;
}

int ATSJoinEvalResponseMessageDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='f' && strcmp(fieldName, "freeDegree")==0) return base+0;
    if (fieldName[0]=='d' && strcmp(fieldName, "dataTimeStamp")==0) return base+1;
    if (fieldName[0]=='p' && strcmp(fieldName, "parentAddress")==0) return base+2;
    if (fieldName[0]=='c' && strcmp(fieldName, "childAddress")==0) return base+3;
    if (fieldName[0]=='c' && strcmp(fieldName, "childDataSeq")==0) return base+4;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *ATSJoinEvalResponseMessageDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "unsigned int",
        "double",
        "TransportAddress",
        "TransportAddress",
        "unsigned int",
    };
    return (field>=0 && field<5) ? fieldTypeStrings[field] : NULL;
}

const char *ATSJoinEvalResponseMessageDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int ATSJoinEvalResponseMessageDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    ATSJoinEvalResponseMessage *pp = (ATSJoinEvalResponseMessage *)object; (void)pp;
    switch (field) {
        case 1: return pp->getDataTimeStampArraySize();
        case 2: return pp->getParentAddressArraySize();
        case 3: return pp->getChildAddressArraySize();
        case 4: return pp->getChildDataSeqArraySize();
        default: return 0;
    }
}

std::string ATSJoinEvalResponseMessageDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    ATSJoinEvalResponseMessage *pp = (ATSJoinEvalResponseMessage *)object; (void)pp;
    switch (field) {
        case 0: return ulong2string(pp->getFreeDegree());
        case 1: return double2string(pp->getDataTimeStamp(i));
        case 2: {std::stringstream out; out << pp->getParentAddress(i); return out.str();}
        case 3: {std::stringstream out; out << pp->getChildAddress(i); return out.str();}
        case 4: return ulong2string(pp->getChildDataSeq(i));
        default: return "";
    }
}

bool ATSJoinEvalResponseMessageDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    ATSJoinEvalResponseMessage *pp = (ATSJoinEvalResponseMessage *)object; (void)pp;
    switch (field) {
        case 0: pp->setFreeDegree(string2ulong(value)); return true;
        case 1: pp->setDataTimeStamp(i,string2double(value)); return true;
        case 4: pp->setChildDataSeq(i,string2ulong(value)); return true;
        default: return false;
    }
}

const char *ATSJoinEvalResponseMessageDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldStructNames[] = {
        NULL,
        NULL,
        "TransportAddress",
        "TransportAddress",
        NULL,
    };
    return (field>=0 && field<5) ? fieldStructNames[field] : NULL;
}

void *ATSJoinEvalResponseMessageDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    ATSJoinEvalResponseMessage *pp = (ATSJoinEvalResponseMessage *)object; (void)pp;
    switch (field) {
        case 2: return (void *)(&pp->getParentAddress(i)); break;
        case 3: return (void *)(&pp->getChildAddress(i)); break;
        default: return NULL;
    }
}

Register_Class(ATSJoinMessage);

ATSJoinMessage::ATSJoinMessage(const char *name, int kind) : ATSMessage(name,kind)
{
    this->setCommand(ATS_JOIN);

    this->dataSeq_var = 0;
}

ATSJoinMessage::ATSJoinMessage(const ATSJoinMessage& other) : ATSMessage()
{
    setName(other.getName());
    operator=(other);
}

ATSJoinMessage::~ATSJoinMessage()
{
}

ATSJoinMessage& ATSJoinMessage::operator=(const ATSJoinMessage& other)
{
    if (this==&other) return *this;
    ATSMessage::operator=(other);
    this->dataSeq_var = other.dataSeq_var;
    return *this;
}

void ATSJoinMessage::parsimPack(cCommBuffer *b)
{
    ATSMessage::parsimPack(b);
    doPacking(b,this->dataSeq_var);
}

void ATSJoinMessage::parsimUnpack(cCommBuffer *b)
{
    ATSMessage::parsimUnpack(b);
    doUnpacking(b,this->dataSeq_var);
}

unsigned int ATSJoinMessage::getDataSeq() const
{
    return dataSeq_var;
}

void ATSJoinMessage::setDataSeq(unsigned int dataSeq_var)
{
    this->dataSeq_var = dataSeq_var;
}

class ATSJoinMessageDescriptor : public cClassDescriptor
{
  public:
    ATSJoinMessageDescriptor();
    virtual ~ATSJoinMessageDescriptor();

    virtual bool doesSupport(cObject *obj) const;
    virtual const char *getProperty(const char *propertyname) const;
    virtual int getFieldCount(void *object) const;
    virtual const char *getFieldName(void *object, int field) const;
    virtual int findField(void *object, const char *fieldName) const;
    virtual unsigned int getFieldTypeFlags(void *object, int field) const;
    virtual const char *getFieldTypeString(void *object, int field) const;
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname) const;
    virtual int getArraySize(void *object, int field) const;

    virtual std::string getFieldAsString(void *object, int field, int i) const;
    virtual bool setFieldAsString(void *object, int field, int i, const char *value) const;

    virtual const char *getFieldStructName(void *object, int field) const;
    virtual void *getFieldStructPointer(void *object, int field, int i) const;
};

Register_ClassDescriptor(ATSJoinMessageDescriptor);

ATSJoinMessageDescriptor::ATSJoinMessageDescriptor() : cClassDescriptor("ATSJoinMessage", "ATSMessage")
{
}

ATSJoinMessageDescriptor::~ATSJoinMessageDescriptor()
{
}

bool ATSJoinMessageDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<ATSJoinMessage *>(obj)!=NULL;
}

const char *ATSJoinMessageDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int ATSJoinMessageDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount(object) : 1;
}

unsigned int ATSJoinMessageDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
    };
    return (field>=0 && field<1) ? fieldTypeFlags[field] : 0;
}

const char *ATSJoinMessageDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "dataSeq",
    };
    return (field>=0 && field<1) ? fieldNames[field] : NULL;
}

int ATSJoinMessageDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='d' && strcmp(fieldName, "dataSeq")==0) return base+0;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *ATSJoinMessageDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "unsigned int",
    };
    return (field>=0 && field<1) ? fieldTypeStrings[field] : NULL;
}

const char *ATSJoinMessageDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int ATSJoinMessageDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    ATSJoinMessage *pp = (ATSJoinMessage *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string ATSJoinMessageDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    ATSJoinMessage *pp = (ATSJoinMessage *)object; (void)pp;
    switch (field) {
        case 0: return ulong2string(pp->getDataSeq());
        default: return "";
    }
}

bool ATSJoinMessageDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    ATSJoinMessage *pp = (ATSJoinMessage *)object; (void)pp;
    switch (field) {
        case 0: pp->setDataSeq(string2ulong(value)); return true;
        default: return false;
    }
}

const char *ATSJoinMessageDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldStructNames[] = {
        NULL,
    };
    return (field>=0 && field<1) ? fieldStructNames[field] : NULL;
}

void *ATSJoinMessageDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    ATSJoinMessage *pp = (ATSJoinMessage *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(ATSJoinResponseMessage);

ATSJoinResponseMessage::ATSJoinResponseMessage(const char *name, int kind) : ATSMessage(name,kind)
{
    this->setCommand(ATS_JOIN_RESPONSE);

    this->dataSeq_var = 0;
}

ATSJoinResponseMessage::ATSJoinResponseMessage(const ATSJoinResponseMessage& other) : ATSMessage()
{
    setName(other.getName());
    operator=(other);
}

ATSJoinResponseMessage::~ATSJoinResponseMessage()
{
}

ATSJoinResponseMessage& ATSJoinResponseMessage::operator=(const ATSJoinResponseMessage& other)
{
    if (this==&other) return *this;
    ATSMessage::operator=(other);
    this->dataSeq_var = other.dataSeq_var;
    return *this;
}

void ATSJoinResponseMessage::parsimPack(cCommBuffer *b)
{
    ATSMessage::parsimPack(b);
    doPacking(b,this->dataSeq_var);
}

void ATSJoinResponseMessage::parsimUnpack(cCommBuffer *b)
{
    ATSMessage::parsimUnpack(b);
    doUnpacking(b,this->dataSeq_var);
}

unsigned int ATSJoinResponseMessage::getDataSeq() const
{
    return dataSeq_var;
}

void ATSJoinResponseMessage::setDataSeq(unsigned int dataSeq_var)
{
    this->dataSeq_var = dataSeq_var;
}

class ATSJoinResponseMessageDescriptor : public cClassDescriptor
{
  public:
    ATSJoinResponseMessageDescriptor();
    virtual ~ATSJoinResponseMessageDescriptor();

    virtual bool doesSupport(cObject *obj) const;
    virtual const char *getProperty(const char *propertyname) const;
    virtual int getFieldCount(void *object) const;
    virtual const char *getFieldName(void *object, int field) const;
    virtual int findField(void *object, const char *fieldName) const;
    virtual unsigned int getFieldTypeFlags(void *object, int field) const;
    virtual const char *getFieldTypeString(void *object, int field) const;
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname) const;
    virtual int getArraySize(void *object, int field) const;

    virtual std::string getFieldAsString(void *object, int field, int i) const;
    virtual bool setFieldAsString(void *object, int field, int i, const char *value) const;

    virtual const char *getFieldStructName(void *object, int field) const;
    virtual void *getFieldStructPointer(void *object, int field, int i) const;
};

Register_ClassDescriptor(ATSJoinResponseMessageDescriptor);

ATSJoinResponseMessageDescriptor::ATSJoinResponseMessageDescriptor() : cClassDescriptor("ATSJoinResponseMessage", "ATSMessage")
{
}

ATSJoinResponseMessageDescriptor::~ATSJoinResponseMessageDescriptor()
{
}

bool ATSJoinResponseMessageDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<ATSJoinResponseMessage *>(obj)!=NULL;
}

const char *ATSJoinResponseMessageDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int ATSJoinResponseMessageDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount(object) : 1;
}

unsigned int ATSJoinResponseMessageDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
    };
    return (field>=0 && field<1) ? fieldTypeFlags[field] : 0;
}

const char *ATSJoinResponseMessageDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "dataSeq",
    };
    return (field>=0 && field<1) ? fieldNames[field] : NULL;
}

int ATSJoinResponseMessageDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='d' && strcmp(fieldName, "dataSeq")==0) return base+0;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *ATSJoinResponseMessageDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "unsigned int",
    };
    return (field>=0 && field<1) ? fieldTypeStrings[field] : NULL;
}

const char *ATSJoinResponseMessageDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int ATSJoinResponseMessageDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    ATSJoinResponseMessage *pp = (ATSJoinResponseMessage *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string ATSJoinResponseMessageDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    ATSJoinResponseMessage *pp = (ATSJoinResponseMessage *)object; (void)pp;
    switch (field) {
        case 0: return ulong2string(pp->getDataSeq());
        default: return "";
    }
}

bool ATSJoinResponseMessageDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    ATSJoinResponseMessage *pp = (ATSJoinResponseMessage *)object; (void)pp;
    switch (field) {
        case 0: pp->setDataSeq(string2ulong(value)); return true;
        default: return false;
    }
}

const char *ATSJoinResponseMessageDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldStructNames[] = {
        NULL,
    };
    return (field>=0 && field<1) ? fieldStructNames[field] : NULL;
}

void *ATSJoinResponseMessageDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    ATSJoinResponseMessage *pp = (ATSJoinResponseMessage *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(ATSInsertMessage);

ATSInsertMessage::ATSInsertMessage(const char *name, int kind) : ATSMessage(name,kind)
{
    this->setCommand(ATS_INSERT);

    this->beChildNode_var = 0;
    this->dataSeq_var = 0;
    this->selectedDataSeq_var = 0;
}

ATSInsertMessage::ATSInsertMessage(const ATSInsertMessage& other) : ATSMessage()
{
    setName(other.getName());
    operator=(other);
}

ATSInsertMessage::~ATSInsertMessage()
{
}

ATSInsertMessage& ATSInsertMessage::operator=(const ATSInsertMessage& other)
{
    if (this==&other) return *this;
    ATSMessage::operator=(other);
    this->beChildNode_var = other.beChildNode_var;
    this->dataSeq_var = other.dataSeq_var;
    this->selectedNodeAddress_var = other.selectedNodeAddress_var;
    this->selectedDataSeq_var = other.selectedDataSeq_var;
    return *this;
}

void ATSInsertMessage::parsimPack(cCommBuffer *b)
{
    ATSMessage::parsimPack(b);
    doPacking(b,this->beChildNode_var);
    doPacking(b,this->dataSeq_var);
    doPacking(b,this->selectedNodeAddress_var);
    doPacking(b,this->selectedDataSeq_var);
}

void ATSInsertMessage::parsimUnpack(cCommBuffer *b)
{
    ATSMessage::parsimUnpack(b);
    doUnpacking(b,this->beChildNode_var);
    doUnpacking(b,this->dataSeq_var);
    doUnpacking(b,this->selectedNodeAddress_var);
    doUnpacking(b,this->selectedDataSeq_var);
}

bool ATSInsertMessage::getBeChildNode() const
{
    return beChildNode_var;
}

void ATSInsertMessage::setBeChildNode(bool beChildNode_var)
{
    this->beChildNode_var = beChildNode_var;
}

unsigned int ATSInsertMessage::getDataSeq() const
{
    return dataSeq_var;
}

void ATSInsertMessage::setDataSeq(unsigned int dataSeq_var)
{
    this->dataSeq_var = dataSeq_var;
}

TransportAddress& ATSInsertMessage::getSelectedNodeAddress()
{
    return selectedNodeAddress_var;
}

void ATSInsertMessage::setSelectedNodeAddress(const TransportAddress& selectedNodeAddress_var)
{
    this->selectedNodeAddress_var = selectedNodeAddress_var;
}

unsigned int ATSInsertMessage::getSelectedDataSeq() const
{
    return selectedDataSeq_var;
}

void ATSInsertMessage::setSelectedDataSeq(unsigned int selectedDataSeq_var)
{
    this->selectedDataSeq_var = selectedDataSeq_var;
}

class ATSInsertMessageDescriptor : public cClassDescriptor
{
  public:
    ATSInsertMessageDescriptor();
    virtual ~ATSInsertMessageDescriptor();

    virtual bool doesSupport(cObject *obj) const;
    virtual const char *getProperty(const char *propertyname) const;
    virtual int getFieldCount(void *object) const;
    virtual const char *getFieldName(void *object, int field) const;
    virtual int findField(void *object, const char *fieldName) const;
    virtual unsigned int getFieldTypeFlags(void *object, int field) const;
    virtual const char *getFieldTypeString(void *object, int field) const;
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname) const;
    virtual int getArraySize(void *object, int field) const;

    virtual std::string getFieldAsString(void *object, int field, int i) const;
    virtual bool setFieldAsString(void *object, int field, int i, const char *value) const;

    virtual const char *getFieldStructName(void *object, int field) const;
    virtual void *getFieldStructPointer(void *object, int field, int i) const;
};

Register_ClassDescriptor(ATSInsertMessageDescriptor);

ATSInsertMessageDescriptor::ATSInsertMessageDescriptor() : cClassDescriptor("ATSInsertMessage", "ATSMessage")
{
}

ATSInsertMessageDescriptor::~ATSInsertMessageDescriptor()
{
}

bool ATSInsertMessageDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<ATSInsertMessage *>(obj)!=NULL;
}

const char *ATSInsertMessageDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int ATSInsertMessageDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 4+basedesc->getFieldCount(object) : 4;
}

unsigned int ATSInsertMessageDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISCOMPOUND,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<4) ? fieldTypeFlags[field] : 0;
}

const char *ATSInsertMessageDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "beChildNode",
        "dataSeq",
        "selectedNodeAddress",
        "selectedDataSeq",
    };
    return (field>=0 && field<4) ? fieldNames[field] : NULL;
}

int ATSInsertMessageDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='b' && strcmp(fieldName, "beChildNode")==0) return base+0;
    if (fieldName[0]=='d' && strcmp(fieldName, "dataSeq")==0) return base+1;
    if (fieldName[0]=='s' && strcmp(fieldName, "selectedNodeAddress")==0) return base+2;
    if (fieldName[0]=='s' && strcmp(fieldName, "selectedDataSeq")==0) return base+3;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *ATSInsertMessageDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "bool",
        "unsigned int",
        "TransportAddress",
        "unsigned int",
    };
    return (field>=0 && field<4) ? fieldTypeStrings[field] : NULL;
}

const char *ATSInsertMessageDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int ATSInsertMessageDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    ATSInsertMessage *pp = (ATSInsertMessage *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string ATSInsertMessageDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    ATSInsertMessage *pp = (ATSInsertMessage *)object; (void)pp;
    switch (field) {
        case 0: return bool2string(pp->getBeChildNode());
        case 1: return ulong2string(pp->getDataSeq());
        case 2: {std::stringstream out; out << pp->getSelectedNodeAddress(); return out.str();}
        case 3: return ulong2string(pp->getSelectedDataSeq());
        default: return "";
    }
}

bool ATSInsertMessageDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    ATSInsertMessage *pp = (ATSInsertMessage *)object; (void)pp;
    switch (field) {
        case 0: pp->setBeChildNode(string2bool(value)); return true;
        case 1: pp->setDataSeq(string2ulong(value)); return true;
        case 3: pp->setSelectedDataSeq(string2ulong(value)); return true;
        default: return false;
    }
}

const char *ATSInsertMessageDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldStructNames[] = {
        NULL,
        NULL,
        "TransportAddress",
        NULL,
    };
    return (field>=0 && field<4) ? fieldStructNames[field] : NULL;
}

void *ATSInsertMessageDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    ATSInsertMessage *pp = (ATSInsertMessage *)object; (void)pp;
    switch (field) {
        case 2: return (void *)(&pp->getSelectedNodeAddress()); break;
        default: return NULL;
    }
}

Register_Class(ATSInsertResponseMessage);

ATSInsertResponseMessage::ATSInsertResponseMessage(const char *name, int kind) : ATSMessage(name,kind)
{
    this->setCommand(ATS_INSERT_RESPONSE);

    this->beChildNode_var = 0;
    this->dataSeq_var = 0;
}

ATSInsertResponseMessage::ATSInsertResponseMessage(const ATSInsertResponseMessage& other) : ATSMessage()
{
    setName(other.getName());
    operator=(other);
}

ATSInsertResponseMessage::~ATSInsertResponseMessage()
{
}

ATSInsertResponseMessage& ATSInsertResponseMessage::operator=(const ATSInsertResponseMessage& other)
{
    if (this==&other) return *this;
    ATSMessage::operator=(other);
    this->beChildNode_var = other.beChildNode_var;
    this->dataSeq_var = other.dataSeq_var;
    return *this;
}

void ATSInsertResponseMessage::parsimPack(cCommBuffer *b)
{
    ATSMessage::parsimPack(b);
    doPacking(b,this->beChildNode_var);
    doPacking(b,this->dataSeq_var);
}

void ATSInsertResponseMessage::parsimUnpack(cCommBuffer *b)
{
    ATSMessage::parsimUnpack(b);
    doUnpacking(b,this->beChildNode_var);
    doUnpacking(b,this->dataSeq_var);
}

bool ATSInsertResponseMessage::getBeChildNode() const
{
    return beChildNode_var;
}

void ATSInsertResponseMessage::setBeChildNode(bool beChildNode_var)
{
    this->beChildNode_var = beChildNode_var;
}

unsigned int ATSInsertResponseMessage::getDataSeq() const
{
    return dataSeq_var;
}

void ATSInsertResponseMessage::setDataSeq(unsigned int dataSeq_var)
{
    this->dataSeq_var = dataSeq_var;
}

class ATSInsertResponseMessageDescriptor : public cClassDescriptor
{
  public:
    ATSInsertResponseMessageDescriptor();
    virtual ~ATSInsertResponseMessageDescriptor();

    virtual bool doesSupport(cObject *obj) const;
    virtual const char *getProperty(const char *propertyname) const;
    virtual int getFieldCount(void *object) const;
    virtual const char *getFieldName(void *object, int field) const;
    virtual int findField(void *object, const char *fieldName) const;
    virtual unsigned int getFieldTypeFlags(void *object, int field) const;
    virtual const char *getFieldTypeString(void *object, int field) const;
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname) const;
    virtual int getArraySize(void *object, int field) const;

    virtual std::string getFieldAsString(void *object, int field, int i) const;
    virtual bool setFieldAsString(void *object, int field, int i, const char *value) const;

    virtual const char *getFieldStructName(void *object, int field) const;
    virtual void *getFieldStructPointer(void *object, int field, int i) const;
};

Register_ClassDescriptor(ATSInsertResponseMessageDescriptor);

ATSInsertResponseMessageDescriptor::ATSInsertResponseMessageDescriptor() : cClassDescriptor("ATSInsertResponseMessage", "ATSMessage")
{
}

ATSInsertResponseMessageDescriptor::~ATSInsertResponseMessageDescriptor()
{
}

bool ATSInsertResponseMessageDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<ATSInsertResponseMessage *>(obj)!=NULL;
}

const char *ATSInsertResponseMessageDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int ATSInsertResponseMessageDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 2+basedesc->getFieldCount(object) : 2;
}

unsigned int ATSInsertResponseMessageDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<2) ? fieldTypeFlags[field] : 0;
}

const char *ATSInsertResponseMessageDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "beChildNode",
        "dataSeq",
    };
    return (field>=0 && field<2) ? fieldNames[field] : NULL;
}

int ATSInsertResponseMessageDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='b' && strcmp(fieldName, "beChildNode")==0) return base+0;
    if (fieldName[0]=='d' && strcmp(fieldName, "dataSeq")==0) return base+1;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *ATSInsertResponseMessageDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "bool",
        "unsigned int",
    };
    return (field>=0 && field<2) ? fieldTypeStrings[field] : NULL;
}

const char *ATSInsertResponseMessageDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int ATSInsertResponseMessageDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    ATSInsertResponseMessage *pp = (ATSInsertResponseMessage *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string ATSInsertResponseMessageDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    ATSInsertResponseMessage *pp = (ATSInsertResponseMessage *)object; (void)pp;
    switch (field) {
        case 0: return bool2string(pp->getBeChildNode());
        case 1: return ulong2string(pp->getDataSeq());
        default: return "";
    }
}

bool ATSInsertResponseMessageDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    ATSInsertResponseMessage *pp = (ATSInsertResponseMessage *)object; (void)pp;
    switch (field) {
        case 0: pp->setBeChildNode(string2bool(value)); return true;
        case 1: pp->setDataSeq(string2ulong(value)); return true;
        default: return false;
    }
}

const char *ATSInsertResponseMessageDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldStructNames[] = {
        NULL,
        NULL,
    };
    return (field>=0 && field<2) ? fieldStructNames[field] : NULL;
}

void *ATSInsertResponseMessageDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    ATSInsertResponseMessage *pp = (ATSInsertResponseMessage *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(ATSJoinSuccessMessage);

ATSJoinSuccessMessage::ATSJoinSuccessMessage(const char *name, int kind) : ATSMessage(name,kind)
{
    this->setCommand(ATS_JOIN_SUCCESS);
}

ATSJoinSuccessMessage::ATSJoinSuccessMessage(const ATSJoinSuccessMessage& other) : ATSMessage()
{
    setName(other.getName());
    operator=(other);
}

ATSJoinSuccessMessage::~ATSJoinSuccessMessage()
{
}

ATSJoinSuccessMessage& ATSJoinSuccessMessage::operator=(const ATSJoinSuccessMessage& other)
{
    if (this==&other) return *this;
    ATSMessage::operator=(other);
    return *this;
}

void ATSJoinSuccessMessage::parsimPack(cCommBuffer *b)
{
    ATSMessage::parsimPack(b);
}

void ATSJoinSuccessMessage::parsimUnpack(cCommBuffer *b)
{
    ATSMessage::parsimUnpack(b);
}

class ATSJoinSuccessMessageDescriptor : public cClassDescriptor
{
  public:
    ATSJoinSuccessMessageDescriptor();
    virtual ~ATSJoinSuccessMessageDescriptor();

    virtual bool doesSupport(cObject *obj) const;
    virtual const char *getProperty(const char *propertyname) const;
    virtual int getFieldCount(void *object) const;
    virtual const char *getFieldName(void *object, int field) const;
    virtual int findField(void *object, const char *fieldName) const;
    virtual unsigned int getFieldTypeFlags(void *object, int field) const;
    virtual const char *getFieldTypeString(void *object, int field) const;
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname) const;
    virtual int getArraySize(void *object, int field) const;

    virtual std::string getFieldAsString(void *object, int field, int i) const;
    virtual bool setFieldAsString(void *object, int field, int i, const char *value) const;

    virtual const char *getFieldStructName(void *object, int field) const;
    virtual void *getFieldStructPointer(void *object, int field, int i) const;
};

Register_ClassDescriptor(ATSJoinSuccessMessageDescriptor);

ATSJoinSuccessMessageDescriptor::ATSJoinSuccessMessageDescriptor() : cClassDescriptor("ATSJoinSuccessMessage", "ATSMessage")
{
}

ATSJoinSuccessMessageDescriptor::~ATSJoinSuccessMessageDescriptor()
{
}

bool ATSJoinSuccessMessageDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<ATSJoinSuccessMessage *>(obj)!=NULL;
}

const char *ATSJoinSuccessMessageDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int ATSJoinSuccessMessageDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 0+basedesc->getFieldCount(object) : 0;
}

unsigned int ATSJoinSuccessMessageDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    return 0;
}

const char *ATSJoinSuccessMessageDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    return NULL;
}

int ATSJoinSuccessMessageDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *ATSJoinSuccessMessageDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    return NULL;
}

const char *ATSJoinSuccessMessageDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int ATSJoinSuccessMessageDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    ATSJoinSuccessMessage *pp = (ATSJoinSuccessMessage *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string ATSJoinSuccessMessageDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    ATSJoinSuccessMessage *pp = (ATSJoinSuccessMessage *)object; (void)pp;
    switch (field) {
        default: return "";
    }
}

bool ATSJoinSuccessMessageDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    ATSJoinSuccessMessage *pp = (ATSJoinSuccessMessage *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *ATSJoinSuccessMessageDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    return NULL;
}

void *ATSJoinSuccessMessageDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    ATSJoinSuccessMessage *pp = (ATSJoinSuccessMessage *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(ATSStatisticMessage);

ATSStatisticMessage::ATSStatisticMessage(const char *name, int kind) : ATSMessage(name,kind)
{
    this->setCommand(ATS_STATISTIC);

    this->createTime_var = 0;
    this->dataSeq_var = 0;
    this->hop_var = 0;
}

ATSStatisticMessage::ATSStatisticMessage(const ATSStatisticMessage& other) : ATSMessage()
{
    setName(other.getName());
    operator=(other);
}

ATSStatisticMessage::~ATSStatisticMessage()
{
}

ATSStatisticMessage& ATSStatisticMessage::operator=(const ATSStatisticMessage& other)
{
    if (this==&other) return *this;
    ATSMessage::operator=(other);
    this->createTime_var = other.createTime_var;
    this->dataSeq_var = other.dataSeq_var;
    this->hop_var = other.hop_var;
    return *this;
}

void ATSStatisticMessage::parsimPack(cCommBuffer *b)
{
    ATSMessage::parsimPack(b);
    doPacking(b,this->createTime_var);
    doPacking(b,this->dataSeq_var);
    doPacking(b,this->hop_var);
}

void ATSStatisticMessage::parsimUnpack(cCommBuffer *b)
{
    ATSMessage::parsimUnpack(b);
    doUnpacking(b,this->createTime_var);
    doUnpacking(b,this->dataSeq_var);
    doUnpacking(b,this->hop_var);
}

double ATSStatisticMessage::getCreateTime() const
{
    return createTime_var;
}

void ATSStatisticMessage::setCreateTime(double createTime_var)
{
    this->createTime_var = createTime_var;
}

unsigned int ATSStatisticMessage::getDataSeq() const
{
    return dataSeq_var;
}

void ATSStatisticMessage::setDataSeq(unsigned int dataSeq_var)
{
    this->dataSeq_var = dataSeq_var;
}

unsigned int ATSStatisticMessage::getHop() const
{
    return hop_var;
}

void ATSStatisticMessage::setHop(unsigned int hop_var)
{
    this->hop_var = hop_var;
}

class ATSStatisticMessageDescriptor : public cClassDescriptor
{
  public:
    ATSStatisticMessageDescriptor();
    virtual ~ATSStatisticMessageDescriptor();

    virtual bool doesSupport(cObject *obj) const;
    virtual const char *getProperty(const char *propertyname) const;
    virtual int getFieldCount(void *object) const;
    virtual const char *getFieldName(void *object, int field) const;
    virtual int findField(void *object, const char *fieldName) const;
    virtual unsigned int getFieldTypeFlags(void *object, int field) const;
    virtual const char *getFieldTypeString(void *object, int field) const;
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname) const;
    virtual int getArraySize(void *object, int field) const;

    virtual std::string getFieldAsString(void *object, int field, int i) const;
    virtual bool setFieldAsString(void *object, int field, int i, const char *value) const;

    virtual const char *getFieldStructName(void *object, int field) const;
    virtual void *getFieldStructPointer(void *object, int field, int i) const;
};

Register_ClassDescriptor(ATSStatisticMessageDescriptor);

ATSStatisticMessageDescriptor::ATSStatisticMessageDescriptor() : cClassDescriptor("ATSStatisticMessage", "ATSMessage")
{
}

ATSStatisticMessageDescriptor::~ATSStatisticMessageDescriptor()
{
}

bool ATSStatisticMessageDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<ATSStatisticMessage *>(obj)!=NULL;
}

const char *ATSStatisticMessageDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int ATSStatisticMessageDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 3+basedesc->getFieldCount(object) : 3;
}

unsigned int ATSStatisticMessageDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<3) ? fieldTypeFlags[field] : 0;
}

const char *ATSStatisticMessageDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "createTime",
        "dataSeq",
        "hop",
    };
    return (field>=0 && field<3) ? fieldNames[field] : NULL;
}

int ATSStatisticMessageDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='c' && strcmp(fieldName, "createTime")==0) return base+0;
    if (fieldName[0]=='d' && strcmp(fieldName, "dataSeq")==0) return base+1;
    if (fieldName[0]=='h' && strcmp(fieldName, "hop")==0) return base+2;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *ATSStatisticMessageDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "double",
        "unsigned int",
        "unsigned int",
    };
    return (field>=0 && field<3) ? fieldTypeStrings[field] : NULL;
}

const char *ATSStatisticMessageDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int ATSStatisticMessageDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    ATSStatisticMessage *pp = (ATSStatisticMessage *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string ATSStatisticMessageDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    ATSStatisticMessage *pp = (ATSStatisticMessage *)object; (void)pp;
    switch (field) {
        case 0: return double2string(pp->getCreateTime());
        case 1: return ulong2string(pp->getDataSeq());
        case 2: return ulong2string(pp->getHop());
        default: return "";
    }
}

bool ATSStatisticMessageDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    ATSStatisticMessage *pp = (ATSStatisticMessage *)object; (void)pp;
    switch (field) {
        case 0: pp->setCreateTime(string2double(value)); return true;
        case 1: pp->setDataSeq(string2ulong(value)); return true;
        case 2: pp->setHop(string2ulong(value)); return true;
        default: return false;
    }
}

const char *ATSStatisticMessageDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldStructNames[] = {
        NULL,
        NULL,
        NULL,
    };
    return (field>=0 && field<3) ? fieldStructNames[field] : NULL;
}

void *ATSStatisticMessageDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    ATSStatisticMessage *pp = (ATSStatisticMessage *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}


