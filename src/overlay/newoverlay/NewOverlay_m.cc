//
// Generated file, do not edit! Created by opp_msgc 4.1 from overlay/newoverlay/NewOverlay.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "NewOverlay_m.h"

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
    cEnum *e = cEnum::find("NEWCommand");
    if (!e) enums.getInstance()->add(e = new cEnum("NEWCommand"));
    e->insert(NEW_QUERY, "NEW_QUERY");
    e->insert(NEW_QUERY_RESPONSE, "NEW_QUERY_RESPONSE");
    e->insert(NEW_JOINEVAL, "NEW_JOINEVAL");
    e->insert(NEW_JOINEVAL_RESPONSE, "NEW_JOINEVAL_RESPONSE");
    e->insert(NEW_JOIN, "NEW_JOIN");
    e->insert(NEW_JOIN_RESPONSE, "NEW_JOIN_RESPONSE");
    e->insert(NEW_INSERT_QUERY, "NEW_INSERT_QUERY");
    e->insert(NEW_INSERT_QUERY_RESPONSE, "NEW_INSERT_QUERY_RESPONSE");
    e->insert(NEW_INSERTEVAL, "NEW_INSERTEVAL");
    e->insert(NEW_INSERTEVAL_RESPONSE, "NEW_INSERTEVAL_RESPONSE");
    e->insert(NEW_INSERT, "NEW_INSERT");
    e->insert(NEW_INSERT_RESPONSE, "NEW_INSERT_RESPONSE");
    e->insert(NEW_JOIN_SUCCESS, "NEW_JOIN_SUCCESS");
    e->insert(NEW_JOIN_STATISTIC, "NEW_JOIN_STATISTIC");
);

Register_Class(NewMessage);

NewMessage::NewMessage(const char *name, int kind) : BaseOverlayMessage(name,kind)
{
    this->command_var = 0;
    this->sentTime_var = 0;
}

NewMessage::NewMessage(const NewMessage& other) : BaseOverlayMessage()
{
    setName(other.getName());
    operator=(other);
}

NewMessage::~NewMessage()
{
}

NewMessage& NewMessage::operator=(const NewMessage& other)
{
    if (this==&other) return *this;
    BaseOverlayMessage::operator=(other);
    this->command_var = other.command_var;
    this->srcNode_var = other.srcNode_var;
    this->sentTime_var = other.sentTime_var;
    return *this;
}

void NewMessage::parsimPack(cCommBuffer *b)
{
    BaseOverlayMessage::parsimPack(b);
    doPacking(b,this->command_var);
    doPacking(b,this->srcNode_var);
    doPacking(b,this->sentTime_var);
}

void NewMessage::parsimUnpack(cCommBuffer *b)
{
    BaseOverlayMessage::parsimUnpack(b);
    doUnpacking(b,this->command_var);
    doUnpacking(b,this->srcNode_var);
    doUnpacking(b,this->sentTime_var);
}

int NewMessage::getCommand() const
{
    return command_var;
}

void NewMessage::setCommand(int command_var)
{
    this->command_var = command_var;
}

TransportAddress& NewMessage::getSrcNode()
{
    return srcNode_var;
}

void NewMessage::setSrcNode(const TransportAddress& srcNode_var)
{
    this->srcNode_var = srcNode_var;
}

simtime_t NewMessage::getSentTime() const
{
    return sentTime_var;
}

void NewMessage::setSentTime(simtime_t sentTime_var)
{
    this->sentTime_var = sentTime_var;
}

class NewMessageDescriptor : public cClassDescriptor
{
  public:
    NewMessageDescriptor();
    virtual ~NewMessageDescriptor();

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

Register_ClassDescriptor(NewMessageDescriptor);

NewMessageDescriptor::NewMessageDescriptor() : cClassDescriptor("NewMessage", "BaseOverlayMessage")
{
}

NewMessageDescriptor::~NewMessageDescriptor()
{
}

bool NewMessageDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<NewMessage *>(obj)!=NULL;
}

const char *NewMessageDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int NewMessageDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 3+basedesc->getFieldCount(object) : 3;
}

unsigned int NewMessageDescriptor::getFieldTypeFlags(void *object, int field) const
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

const char *NewMessageDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "command",
        "srcNode",
        "sentTime",
    };
    return (field>=0 && field<3) ? fieldNames[field] : NULL;
}

int NewMessageDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='c' && strcmp(fieldName, "command")==0) return base+0;
    if (fieldName[0]=='s' && strcmp(fieldName, "srcNode")==0) return base+1;
    if (fieldName[0]=='s' && strcmp(fieldName, "sentTime")==0) return base+2;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *NewMessageDescriptor::getFieldTypeString(void *object, int field) const
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
        "simtime_t",
    };
    return (field>=0 && field<3) ? fieldTypeStrings[field] : NULL;
}

const char *NewMessageDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0:
            if (!strcmp(propertyname,"enum")) return "NEWCommand";
            return NULL;
        default: return NULL;
    }
}

int NewMessageDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    NewMessage *pp = (NewMessage *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string NewMessageDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    NewMessage *pp = (NewMessage *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getCommand());
        case 1: {std::stringstream out; out << pp->getSrcNode(); return out.str();}
        case 2: return double2string(pp->getSentTime());
        default: return "";
    }
}

bool NewMessageDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    NewMessage *pp = (NewMessage *)object; (void)pp;
    switch (field) {
        case 0: pp->setCommand(string2long(value)); return true;
        case 2: pp->setSentTime(string2double(value)); return true;
        default: return false;
    }
}

const char *NewMessageDescriptor::getFieldStructName(void *object, int field) const
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

void *NewMessageDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    NewMessage *pp = (NewMessage *)object; (void)pp;
    switch (field) {
        case 1: return (void *)(&pp->getSrcNode()); break;
        default: return NULL;
    }
}

Register_Class(NewQueryMessage);

NewQueryMessage::NewQueryMessage(const char *name, int kind) : NewMessage(name,kind)
{
}

NewQueryMessage::NewQueryMessage(const NewQueryMessage& other) : NewMessage()
{
    setName(other.getName());
    operator=(other);
}

NewQueryMessage::~NewQueryMessage()
{
}

NewQueryMessage& NewQueryMessage::operator=(const NewQueryMessage& other)
{
    if (this==&other) return *this;
    NewMessage::operator=(other);
    return *this;
}

void NewQueryMessage::parsimPack(cCommBuffer *b)
{
    NewMessage::parsimPack(b);
}

void NewQueryMessage::parsimUnpack(cCommBuffer *b)
{
    NewMessage::parsimUnpack(b);
}

class NewQueryMessageDescriptor : public cClassDescriptor
{
  public:
    NewQueryMessageDescriptor();
    virtual ~NewQueryMessageDescriptor();

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

Register_ClassDescriptor(NewQueryMessageDescriptor);

NewQueryMessageDescriptor::NewQueryMessageDescriptor() : cClassDescriptor("NewQueryMessage", "NewMessage")
{
}

NewQueryMessageDescriptor::~NewQueryMessageDescriptor()
{
}

bool NewQueryMessageDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<NewQueryMessage *>(obj)!=NULL;
}

const char *NewQueryMessageDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int NewQueryMessageDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 0+basedesc->getFieldCount(object) : 0;
}

unsigned int NewQueryMessageDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    return 0;
}

const char *NewQueryMessageDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    return NULL;
}

int NewQueryMessageDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *NewQueryMessageDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    return NULL;
}

const char *NewQueryMessageDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int NewQueryMessageDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    NewQueryMessage *pp = (NewQueryMessage *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string NewQueryMessageDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    NewQueryMessage *pp = (NewQueryMessage *)object; (void)pp;
    switch (field) {
        default: return "";
    }
}

bool NewQueryMessageDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    NewQueryMessage *pp = (NewQueryMessage *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *NewQueryMessageDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    return NULL;
}

void *NewQueryMessageDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    NewQueryMessage *pp = (NewQueryMessage *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(NewQueryResponseMessage);

NewQueryResponseMessage::NewQueryResponseMessage(const char *name, int kind) : NewMessage(name,kind)
{
    members_arraysize = 0;
    this->members_var = 0;
    this->freeDegree_var = 0;
}

NewQueryResponseMessage::NewQueryResponseMessage(const NewQueryResponseMessage& other) : NewMessage()
{
    setName(other.getName());
    members_arraysize = 0;
    this->members_var = 0;
    operator=(other);
}

NewQueryResponseMessage::~NewQueryResponseMessage()
{
    delete [] members_var;
}

NewQueryResponseMessage& NewQueryResponseMessage::operator=(const NewQueryResponseMessage& other)
{
    if (this==&other) return *this;
    NewMessage::operator=(other);
    delete [] this->members_var;
    this->members_var = (other.members_arraysize==0) ? NULL : new ::TransportAddress[other.members_arraysize];
    members_arraysize = other.members_arraysize;
    for (unsigned int i=0; i<members_arraysize; i++)
        this->members_var[i] = other.members_var[i];
    this->freeDegree_var = other.freeDegree_var;
    return *this;
}

void NewQueryResponseMessage::parsimPack(cCommBuffer *b)
{
    NewMessage::parsimPack(b);
    b->pack(members_arraysize);
    doPacking(b,this->members_var,members_arraysize);
    doPacking(b,this->freeDegree_var);
}

void NewQueryResponseMessage::parsimUnpack(cCommBuffer *b)
{
    NewMessage::parsimUnpack(b);
    delete [] this->members_var;
    b->unpack(members_arraysize);
    if (members_arraysize==0) {
        this->members_var = 0;
    } else {
        this->members_var = new ::TransportAddress[members_arraysize];
        doUnpacking(b,this->members_var,members_arraysize);
    }
    doUnpacking(b,this->freeDegree_var);
}

void NewQueryResponseMessage::setMembersArraySize(unsigned int size)
{
    ::TransportAddress *members_var2 = (size==0) ? NULL : new ::TransportAddress[size];
    unsigned int sz = members_arraysize < size ? members_arraysize : size;
    for (unsigned int i=0; i<sz; i++)
        members_var2[i] = this->members_var[i];
    members_arraysize = size;
    delete [] this->members_var;
    this->members_var = members_var2;
}

unsigned int NewQueryResponseMessage::getMembersArraySize() const
{
    return members_arraysize;
}

TransportAddress& NewQueryResponseMessage::getMembers(unsigned int k)
{
    if (k>=members_arraysize) throw cRuntimeError("Array of size %d indexed by %d", members_arraysize, k);
    return members_var[k];
}

void NewQueryResponseMessage::setMembers(unsigned int k, const TransportAddress& members_var)
{
    if (k>=members_arraysize) throw cRuntimeError("Array of size %d indexed by %d", members_arraysize, k);
    this->members_var[k]=members_var;
}

unsigned int NewQueryResponseMessage::getFreeDegree() const
{
    return freeDegree_var;
}

void NewQueryResponseMessage::setFreeDegree(unsigned int freeDegree_var)
{
    this->freeDegree_var = freeDegree_var;
}

class NewQueryResponseMessageDescriptor : public cClassDescriptor
{
  public:
    NewQueryResponseMessageDescriptor();
    virtual ~NewQueryResponseMessageDescriptor();

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

Register_ClassDescriptor(NewQueryResponseMessageDescriptor);

NewQueryResponseMessageDescriptor::NewQueryResponseMessageDescriptor() : cClassDescriptor("NewQueryResponseMessage", "NewMessage")
{
}

NewQueryResponseMessageDescriptor::~NewQueryResponseMessageDescriptor()
{
}

bool NewQueryResponseMessageDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<NewQueryResponseMessage *>(obj)!=NULL;
}

const char *NewQueryResponseMessageDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int NewQueryResponseMessageDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 2+basedesc->getFieldCount(object) : 2;
}

unsigned int NewQueryResponseMessageDescriptor::getFieldTypeFlags(void *object, int field) const
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

const char *NewQueryResponseMessageDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "members",
        "freeDegree",
    };
    return (field>=0 && field<2) ? fieldNames[field] : NULL;
}

int NewQueryResponseMessageDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='m' && strcmp(fieldName, "members")==0) return base+0;
    if (fieldName[0]=='f' && strcmp(fieldName, "freeDegree")==0) return base+1;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *NewQueryResponseMessageDescriptor::getFieldTypeString(void *object, int field) const
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

const char *NewQueryResponseMessageDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int NewQueryResponseMessageDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    NewQueryResponseMessage *pp = (NewQueryResponseMessage *)object; (void)pp;
    switch (field) {
        case 0: return pp->getMembersArraySize();
        default: return 0;
    }
}

std::string NewQueryResponseMessageDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    NewQueryResponseMessage *pp = (NewQueryResponseMessage *)object; (void)pp;
    switch (field) {
        case 0: {std::stringstream out; out << pp->getMembers(i); return out.str();}
        case 1: return ulong2string(pp->getFreeDegree());
        default: return "";
    }
}

bool NewQueryResponseMessageDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    NewQueryResponseMessage *pp = (NewQueryResponseMessage *)object; (void)pp;
    switch (field) {
        case 1: pp->setFreeDegree(string2ulong(value)); return true;
        default: return false;
    }
}

const char *NewQueryResponseMessageDescriptor::getFieldStructName(void *object, int field) const
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

void *NewQueryResponseMessageDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    NewQueryResponseMessage *pp = (NewQueryResponseMessage *)object; (void)pp;
    switch (field) {
        case 0: return (void *)(&pp->getMembers(i)); break;
        default: return NULL;
    }
}

Register_Class(NewJoinEvalMessage);

NewJoinEvalMessage::NewJoinEvalMessage(const char *name, int kind) : NewMessage(name,kind)
{
}

NewJoinEvalMessage::NewJoinEvalMessage(const NewJoinEvalMessage& other) : NewMessage()
{
    setName(other.getName());
    operator=(other);
}

NewJoinEvalMessage::~NewJoinEvalMessage()
{
}

NewJoinEvalMessage& NewJoinEvalMessage::operator=(const NewJoinEvalMessage& other)
{
    if (this==&other) return *this;
    NewMessage::operator=(other);
    return *this;
}

void NewJoinEvalMessage::parsimPack(cCommBuffer *b)
{
    NewMessage::parsimPack(b);
}

void NewJoinEvalMessage::parsimUnpack(cCommBuffer *b)
{
    NewMessage::parsimUnpack(b);
}

class NewJoinEvalMessageDescriptor : public cClassDescriptor
{
  public:
    NewJoinEvalMessageDescriptor();
    virtual ~NewJoinEvalMessageDescriptor();

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

Register_ClassDescriptor(NewJoinEvalMessageDescriptor);

NewJoinEvalMessageDescriptor::NewJoinEvalMessageDescriptor() : cClassDescriptor("NewJoinEvalMessage", "NewMessage")
{
}

NewJoinEvalMessageDescriptor::~NewJoinEvalMessageDescriptor()
{
}

bool NewJoinEvalMessageDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<NewJoinEvalMessage *>(obj)!=NULL;
}

const char *NewJoinEvalMessageDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int NewJoinEvalMessageDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 0+basedesc->getFieldCount(object) : 0;
}

unsigned int NewJoinEvalMessageDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    return 0;
}

const char *NewJoinEvalMessageDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    return NULL;
}

int NewJoinEvalMessageDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *NewJoinEvalMessageDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    return NULL;
}

const char *NewJoinEvalMessageDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int NewJoinEvalMessageDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    NewJoinEvalMessage *pp = (NewJoinEvalMessage *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string NewJoinEvalMessageDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    NewJoinEvalMessage *pp = (NewJoinEvalMessage *)object; (void)pp;
    switch (field) {
        default: return "";
    }
}

bool NewJoinEvalMessageDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    NewJoinEvalMessage *pp = (NewJoinEvalMessage *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *NewJoinEvalMessageDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    return NULL;
}

void *NewJoinEvalMessageDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    NewJoinEvalMessage *pp = (NewJoinEvalMessage *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(NewJoinEvalResponseMessage);

NewJoinEvalResponseMessage::NewJoinEvalResponseMessage(const char *name, int kind) : NewMessage(name,kind)
{
    this->freeDegree_var = 0;
    dataTimeStamp_arraysize = 0;
    this->dataTimeStamp_var = 0;
    parentNode_arraysize = 0;
    this->parentNode_var = 0;
    childNode_arraysize = 0;
    this->childNode_var = 0;
    childDataSeq_arraysize = 0;
    this->childDataSeq_var = 0;
}

NewJoinEvalResponseMessage::NewJoinEvalResponseMessage(const NewJoinEvalResponseMessage& other) : NewMessage()
{
    setName(other.getName());
    dataTimeStamp_arraysize = 0;
    this->dataTimeStamp_var = 0;
    parentNode_arraysize = 0;
    this->parentNode_var = 0;
    childNode_arraysize = 0;
    this->childNode_var = 0;
    childDataSeq_arraysize = 0;
    this->childDataSeq_var = 0;
    operator=(other);
}

NewJoinEvalResponseMessage::~NewJoinEvalResponseMessage()
{
    delete [] dataTimeStamp_var;
    delete [] parentNode_var;
    delete [] childNode_var;
    delete [] childDataSeq_var;
}

NewJoinEvalResponseMessage& NewJoinEvalResponseMessage::operator=(const NewJoinEvalResponseMessage& other)
{
    if (this==&other) return *this;
    NewMessage::operator=(other);
    this->freeDegree_var = other.freeDegree_var;
    delete [] this->dataTimeStamp_var;
    this->dataTimeStamp_var = (other.dataTimeStamp_arraysize==0) ? NULL : new simtime_t[other.dataTimeStamp_arraysize];
    dataTimeStamp_arraysize = other.dataTimeStamp_arraysize;
    for (unsigned int i=0; i<dataTimeStamp_arraysize; i++)
        this->dataTimeStamp_var[i] = other.dataTimeStamp_var[i];
    delete [] this->parentNode_var;
    this->parentNode_var = (other.parentNode_arraysize==0) ? NULL : new ::TransportAddress[other.parentNode_arraysize];
    parentNode_arraysize = other.parentNode_arraysize;
    for (unsigned int i=0; i<parentNode_arraysize; i++)
        this->parentNode_var[i] = other.parentNode_var[i];
    delete [] this->childNode_var;
    this->childNode_var = (other.childNode_arraysize==0) ? NULL : new ::TransportAddress[other.childNode_arraysize];
    childNode_arraysize = other.childNode_arraysize;
    for (unsigned int i=0; i<childNode_arraysize; i++)
        this->childNode_var[i] = other.childNode_var[i];
    delete [] this->childDataSeq_var;
    this->childDataSeq_var = (other.childDataSeq_arraysize==0) ? NULL : new unsigned int[other.childDataSeq_arraysize];
    childDataSeq_arraysize = other.childDataSeq_arraysize;
    for (unsigned int i=0; i<childDataSeq_arraysize; i++)
        this->childDataSeq_var[i] = other.childDataSeq_var[i];
    return *this;
}

void NewJoinEvalResponseMessage::parsimPack(cCommBuffer *b)
{
    NewMessage::parsimPack(b);
    doPacking(b,this->freeDegree_var);
    b->pack(dataTimeStamp_arraysize);
    doPacking(b,this->dataTimeStamp_var,dataTimeStamp_arraysize);
    b->pack(parentNode_arraysize);
    doPacking(b,this->parentNode_var,parentNode_arraysize);
    b->pack(childNode_arraysize);
    doPacking(b,this->childNode_var,childNode_arraysize);
    b->pack(childDataSeq_arraysize);
    doPacking(b,this->childDataSeq_var,childDataSeq_arraysize);
}

void NewJoinEvalResponseMessage::parsimUnpack(cCommBuffer *b)
{
    NewMessage::parsimUnpack(b);
    doUnpacking(b,this->freeDegree_var);
    delete [] this->dataTimeStamp_var;
    b->unpack(dataTimeStamp_arraysize);
    if (dataTimeStamp_arraysize==0) {
        this->dataTimeStamp_var = 0;
    } else {
        this->dataTimeStamp_var = new simtime_t[dataTimeStamp_arraysize];
        doUnpacking(b,this->dataTimeStamp_var,dataTimeStamp_arraysize);
    }
    delete [] this->parentNode_var;
    b->unpack(parentNode_arraysize);
    if (parentNode_arraysize==0) {
        this->parentNode_var = 0;
    } else {
        this->parentNode_var = new ::TransportAddress[parentNode_arraysize];
        doUnpacking(b,this->parentNode_var,parentNode_arraysize);
    }
    delete [] this->childNode_var;
    b->unpack(childNode_arraysize);
    if (childNode_arraysize==0) {
        this->childNode_var = 0;
    } else {
        this->childNode_var = new ::TransportAddress[childNode_arraysize];
        doUnpacking(b,this->childNode_var,childNode_arraysize);
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

unsigned int NewJoinEvalResponseMessage::getFreeDegree() const
{
    return freeDegree_var;
}

void NewJoinEvalResponseMessage::setFreeDegree(unsigned int freeDegree_var)
{
    this->freeDegree_var = freeDegree_var;
}

void NewJoinEvalResponseMessage::setDataTimeStampArraySize(unsigned int size)
{
    simtime_t *dataTimeStamp_var2 = (size==0) ? NULL : new simtime_t[size];
    unsigned int sz = dataTimeStamp_arraysize < size ? dataTimeStamp_arraysize : size;
    for (unsigned int i=0; i<sz; i++)
        dataTimeStamp_var2[i] = this->dataTimeStamp_var[i];
    for (unsigned int i=sz; i<size; i++)
        dataTimeStamp_var2[i] = 0;
    dataTimeStamp_arraysize = size;
    delete [] this->dataTimeStamp_var;
    this->dataTimeStamp_var = dataTimeStamp_var2;
}

unsigned int NewJoinEvalResponseMessage::getDataTimeStampArraySize() const
{
    return dataTimeStamp_arraysize;
}

simtime_t NewJoinEvalResponseMessage::getDataTimeStamp(unsigned int k) const
{
    if (k>=dataTimeStamp_arraysize) throw cRuntimeError("Array of size %d indexed by %d", dataTimeStamp_arraysize, k);
    return dataTimeStamp_var[k];
}

void NewJoinEvalResponseMessage::setDataTimeStamp(unsigned int k, simtime_t dataTimeStamp_var)
{
    if (k>=dataTimeStamp_arraysize) throw cRuntimeError("Array of size %d indexed by %d", dataTimeStamp_arraysize, k);
    this->dataTimeStamp_var[k]=dataTimeStamp_var;
}

void NewJoinEvalResponseMessage::setParentNodeArraySize(unsigned int size)
{
    ::TransportAddress *parentNode_var2 = (size==0) ? NULL : new ::TransportAddress[size];
    unsigned int sz = parentNode_arraysize < size ? parentNode_arraysize : size;
    for (unsigned int i=0; i<sz; i++)
        parentNode_var2[i] = this->parentNode_var[i];
    parentNode_arraysize = size;
    delete [] this->parentNode_var;
    this->parentNode_var = parentNode_var2;
}

unsigned int NewJoinEvalResponseMessage::getParentNodeArraySize() const
{
    return parentNode_arraysize;
}

TransportAddress& NewJoinEvalResponseMessage::getParentNode(unsigned int k)
{
    if (k>=parentNode_arraysize) throw cRuntimeError("Array of size %d indexed by %d", parentNode_arraysize, k);
    return parentNode_var[k];
}

void NewJoinEvalResponseMessage::setParentNode(unsigned int k, const TransportAddress& parentNode_var)
{
    if (k>=parentNode_arraysize) throw cRuntimeError("Array of size %d indexed by %d", parentNode_arraysize, k);
    this->parentNode_var[k]=parentNode_var;
}

void NewJoinEvalResponseMessage::setChildNodeArraySize(unsigned int size)
{
    ::TransportAddress *childNode_var2 = (size==0) ? NULL : new ::TransportAddress[size];
    unsigned int sz = childNode_arraysize < size ? childNode_arraysize : size;
    for (unsigned int i=0; i<sz; i++)
        childNode_var2[i] = this->childNode_var[i];
    childNode_arraysize = size;
    delete [] this->childNode_var;
    this->childNode_var = childNode_var2;
}

unsigned int NewJoinEvalResponseMessage::getChildNodeArraySize() const
{
    return childNode_arraysize;
}

TransportAddress& NewJoinEvalResponseMessage::getChildNode(unsigned int k)
{
    if (k>=childNode_arraysize) throw cRuntimeError("Array of size %d indexed by %d", childNode_arraysize, k);
    return childNode_var[k];
}

void NewJoinEvalResponseMessage::setChildNode(unsigned int k, const TransportAddress& childNode_var)
{
    if (k>=childNode_arraysize) throw cRuntimeError("Array of size %d indexed by %d", childNode_arraysize, k);
    this->childNode_var[k]=childNode_var;
}

void NewJoinEvalResponseMessage::setChildDataSeqArraySize(unsigned int size)
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

unsigned int NewJoinEvalResponseMessage::getChildDataSeqArraySize() const
{
    return childDataSeq_arraysize;
}

unsigned int NewJoinEvalResponseMessage::getChildDataSeq(unsigned int k) const
{
    if (k>=childDataSeq_arraysize) throw cRuntimeError("Array of size %d indexed by %d", childDataSeq_arraysize, k);
    return childDataSeq_var[k];
}

void NewJoinEvalResponseMessage::setChildDataSeq(unsigned int k, unsigned int childDataSeq_var)
{
    if (k>=childDataSeq_arraysize) throw cRuntimeError("Array of size %d indexed by %d", childDataSeq_arraysize, k);
    this->childDataSeq_var[k]=childDataSeq_var;
}

class NewJoinEvalResponseMessageDescriptor : public cClassDescriptor
{
  public:
    NewJoinEvalResponseMessageDescriptor();
    virtual ~NewJoinEvalResponseMessageDescriptor();

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

Register_ClassDescriptor(NewJoinEvalResponseMessageDescriptor);

NewJoinEvalResponseMessageDescriptor::NewJoinEvalResponseMessageDescriptor() : cClassDescriptor("NewJoinEvalResponseMessage", "NewMessage")
{
}

NewJoinEvalResponseMessageDescriptor::~NewJoinEvalResponseMessageDescriptor()
{
}

bool NewJoinEvalResponseMessageDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<NewJoinEvalResponseMessage *>(obj)!=NULL;
}

const char *NewJoinEvalResponseMessageDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int NewJoinEvalResponseMessageDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 5+basedesc->getFieldCount(object) : 5;
}

unsigned int NewJoinEvalResponseMessageDescriptor::getFieldTypeFlags(void *object, int field) const
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

const char *NewJoinEvalResponseMessageDescriptor::getFieldName(void *object, int field) const
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
        "parentNode",
        "childNode",
        "childDataSeq",
    };
    return (field>=0 && field<5) ? fieldNames[field] : NULL;
}

int NewJoinEvalResponseMessageDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='f' && strcmp(fieldName, "freeDegree")==0) return base+0;
    if (fieldName[0]=='d' && strcmp(fieldName, "dataTimeStamp")==0) return base+1;
    if (fieldName[0]=='p' && strcmp(fieldName, "parentNode")==0) return base+2;
    if (fieldName[0]=='c' && strcmp(fieldName, "childNode")==0) return base+3;
    if (fieldName[0]=='c' && strcmp(fieldName, "childDataSeq")==0) return base+4;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *NewJoinEvalResponseMessageDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "unsigned int",
        "simtime_t",
        "TransportAddress",
        "TransportAddress",
        "unsigned int",
    };
    return (field>=0 && field<5) ? fieldTypeStrings[field] : NULL;
}

const char *NewJoinEvalResponseMessageDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int NewJoinEvalResponseMessageDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    NewJoinEvalResponseMessage *pp = (NewJoinEvalResponseMessage *)object; (void)pp;
    switch (field) {
        case 1: return pp->getDataTimeStampArraySize();
        case 2: return pp->getParentNodeArraySize();
        case 3: return pp->getChildNodeArraySize();
        case 4: return pp->getChildDataSeqArraySize();
        default: return 0;
    }
}

std::string NewJoinEvalResponseMessageDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    NewJoinEvalResponseMessage *pp = (NewJoinEvalResponseMessage *)object; (void)pp;
    switch (field) {
        case 0: return ulong2string(pp->getFreeDegree());
        case 1: return double2string(pp->getDataTimeStamp(i));
        case 2: {std::stringstream out; out << pp->getParentNode(i); return out.str();}
        case 3: {std::stringstream out; out << pp->getChildNode(i); return out.str();}
        case 4: return ulong2string(pp->getChildDataSeq(i));
        default: return "";
    }
}

bool NewJoinEvalResponseMessageDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    NewJoinEvalResponseMessage *pp = (NewJoinEvalResponseMessage *)object; (void)pp;
    switch (field) {
        case 0: pp->setFreeDegree(string2ulong(value)); return true;
        case 1: pp->setDataTimeStamp(i,string2double(value)); return true;
        case 4: pp->setChildDataSeq(i,string2ulong(value)); return true;
        default: return false;
    }
}

const char *NewJoinEvalResponseMessageDescriptor::getFieldStructName(void *object, int field) const
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

void *NewJoinEvalResponseMessageDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    NewJoinEvalResponseMessage *pp = (NewJoinEvalResponseMessage *)object; (void)pp;
    switch (field) {
        case 2: return (void *)(&pp->getParentNode(i)); break;
        case 3: return (void *)(&pp->getChildNode(i)); break;
        default: return NULL;
    }
}

Register_Class(NewJoinMessage);

NewJoinMessage::NewJoinMessage(const char *name, int kind) : NewMessage(name,kind)
{
    this->dataSeq_var = 0;
}

NewJoinMessage::NewJoinMessage(const NewJoinMessage& other) : NewMessage()
{
    setName(other.getName());
    operator=(other);
}

NewJoinMessage::~NewJoinMessage()
{
}

NewJoinMessage& NewJoinMessage::operator=(const NewJoinMessage& other)
{
    if (this==&other) return *this;
    NewMessage::operator=(other);
    this->dataSeq_var = other.dataSeq_var;
    return *this;
}

void NewJoinMessage::parsimPack(cCommBuffer *b)
{
    NewMessage::parsimPack(b);
    doPacking(b,this->dataSeq_var);
}

void NewJoinMessage::parsimUnpack(cCommBuffer *b)
{
    NewMessage::parsimUnpack(b);
    doUnpacking(b,this->dataSeq_var);
}

unsigned int NewJoinMessage::getDataSeq() const
{
    return dataSeq_var;
}

void NewJoinMessage::setDataSeq(unsigned int dataSeq_var)
{
    this->dataSeq_var = dataSeq_var;
}

class NewJoinMessageDescriptor : public cClassDescriptor
{
  public:
    NewJoinMessageDescriptor();
    virtual ~NewJoinMessageDescriptor();

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

Register_ClassDescriptor(NewJoinMessageDescriptor);

NewJoinMessageDescriptor::NewJoinMessageDescriptor() : cClassDescriptor("NewJoinMessage", "NewMessage")
{
}

NewJoinMessageDescriptor::~NewJoinMessageDescriptor()
{
}

bool NewJoinMessageDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<NewJoinMessage *>(obj)!=NULL;
}

const char *NewJoinMessageDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int NewJoinMessageDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount(object) : 1;
}

unsigned int NewJoinMessageDescriptor::getFieldTypeFlags(void *object, int field) const
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

const char *NewJoinMessageDescriptor::getFieldName(void *object, int field) const
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

int NewJoinMessageDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='d' && strcmp(fieldName, "dataSeq")==0) return base+0;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *NewJoinMessageDescriptor::getFieldTypeString(void *object, int field) const
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

const char *NewJoinMessageDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int NewJoinMessageDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    NewJoinMessage *pp = (NewJoinMessage *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string NewJoinMessageDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    NewJoinMessage *pp = (NewJoinMessage *)object; (void)pp;
    switch (field) {
        case 0: return ulong2string(pp->getDataSeq());
        default: return "";
    }
}

bool NewJoinMessageDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    NewJoinMessage *pp = (NewJoinMessage *)object; (void)pp;
    switch (field) {
        case 0: pp->setDataSeq(string2ulong(value)); return true;
        default: return false;
    }
}

const char *NewJoinMessageDescriptor::getFieldStructName(void *object, int field) const
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

void *NewJoinMessageDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    NewJoinMessage *pp = (NewJoinMessage *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(NewJoinResponseMessage);

NewJoinResponseMessage::NewJoinResponseMessage(const char *name, int kind) : NewMessage(name,kind)
{
    this->dataSeq_var = 0;
}

NewJoinResponseMessage::NewJoinResponseMessage(const NewJoinResponseMessage& other) : NewMessage()
{
    setName(other.getName());
    operator=(other);
}

NewJoinResponseMessage::~NewJoinResponseMessage()
{
}

NewJoinResponseMessage& NewJoinResponseMessage::operator=(const NewJoinResponseMessage& other)
{
    if (this==&other) return *this;
    NewMessage::operator=(other);
    this->dataSeq_var = other.dataSeq_var;
    return *this;
}

void NewJoinResponseMessage::parsimPack(cCommBuffer *b)
{
    NewMessage::parsimPack(b);
    doPacking(b,this->dataSeq_var);
}

void NewJoinResponseMessage::parsimUnpack(cCommBuffer *b)
{
    NewMessage::parsimUnpack(b);
    doUnpacking(b,this->dataSeq_var);
}

unsigned int NewJoinResponseMessage::getDataSeq() const
{
    return dataSeq_var;
}

void NewJoinResponseMessage::setDataSeq(unsigned int dataSeq_var)
{
    this->dataSeq_var = dataSeq_var;
}

class NewJoinResponseMessageDescriptor : public cClassDescriptor
{
  public:
    NewJoinResponseMessageDescriptor();
    virtual ~NewJoinResponseMessageDescriptor();

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

Register_ClassDescriptor(NewJoinResponseMessageDescriptor);

NewJoinResponseMessageDescriptor::NewJoinResponseMessageDescriptor() : cClassDescriptor("NewJoinResponseMessage", "NewMessage")
{
}

NewJoinResponseMessageDescriptor::~NewJoinResponseMessageDescriptor()
{
}

bool NewJoinResponseMessageDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<NewJoinResponseMessage *>(obj)!=NULL;
}

const char *NewJoinResponseMessageDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int NewJoinResponseMessageDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount(object) : 1;
}

unsigned int NewJoinResponseMessageDescriptor::getFieldTypeFlags(void *object, int field) const
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

const char *NewJoinResponseMessageDescriptor::getFieldName(void *object, int field) const
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

int NewJoinResponseMessageDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='d' && strcmp(fieldName, "dataSeq")==0) return base+0;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *NewJoinResponseMessageDescriptor::getFieldTypeString(void *object, int field) const
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

const char *NewJoinResponseMessageDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int NewJoinResponseMessageDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    NewJoinResponseMessage *pp = (NewJoinResponseMessage *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string NewJoinResponseMessageDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    NewJoinResponseMessage *pp = (NewJoinResponseMessage *)object; (void)pp;
    switch (field) {
        case 0: return ulong2string(pp->getDataSeq());
        default: return "";
    }
}

bool NewJoinResponseMessageDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    NewJoinResponseMessage *pp = (NewJoinResponseMessage *)object; (void)pp;
    switch (field) {
        case 0: pp->setDataSeq(string2ulong(value)); return true;
        default: return false;
    }
}

const char *NewJoinResponseMessageDescriptor::getFieldStructName(void *object, int field) const
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

void *NewJoinResponseMessageDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    NewJoinResponseMessage *pp = (NewJoinResponseMessage *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(NewInsertQueryMessage);

NewInsertQueryMessage::NewInsertQueryMessage(const char *name, int kind) : NewMessage(name,kind)
{
    this->dataSeq_var = 0;
}

NewInsertQueryMessage::NewInsertQueryMessage(const NewInsertQueryMessage& other) : NewMessage()
{
    setName(other.getName());
    operator=(other);
}

NewInsertQueryMessage::~NewInsertQueryMessage()
{
}

NewInsertQueryMessage& NewInsertQueryMessage::operator=(const NewInsertQueryMessage& other)
{
    if (this==&other) return *this;
    NewMessage::operator=(other);
    this->dataSeq_var = other.dataSeq_var;
    return *this;
}

void NewInsertQueryMessage::parsimPack(cCommBuffer *b)
{
    NewMessage::parsimPack(b);
    doPacking(b,this->dataSeq_var);
}

void NewInsertQueryMessage::parsimUnpack(cCommBuffer *b)
{
    NewMessage::parsimUnpack(b);
    doUnpacking(b,this->dataSeq_var);
}

unsigned int NewInsertQueryMessage::getDataSeq() const
{
    return dataSeq_var;
}

void NewInsertQueryMessage::setDataSeq(unsigned int dataSeq_var)
{
    this->dataSeq_var = dataSeq_var;
}

class NewInsertQueryMessageDescriptor : public cClassDescriptor
{
  public:
    NewInsertQueryMessageDescriptor();
    virtual ~NewInsertQueryMessageDescriptor();

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

Register_ClassDescriptor(NewInsertQueryMessageDescriptor);

NewInsertQueryMessageDescriptor::NewInsertQueryMessageDescriptor() : cClassDescriptor("NewInsertQueryMessage", "NewMessage")
{
}

NewInsertQueryMessageDescriptor::~NewInsertQueryMessageDescriptor()
{
}

bool NewInsertQueryMessageDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<NewInsertQueryMessage *>(obj)!=NULL;
}

const char *NewInsertQueryMessageDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int NewInsertQueryMessageDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount(object) : 1;
}

unsigned int NewInsertQueryMessageDescriptor::getFieldTypeFlags(void *object, int field) const
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

const char *NewInsertQueryMessageDescriptor::getFieldName(void *object, int field) const
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

int NewInsertQueryMessageDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='d' && strcmp(fieldName, "dataSeq")==0) return base+0;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *NewInsertQueryMessageDescriptor::getFieldTypeString(void *object, int field) const
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

const char *NewInsertQueryMessageDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int NewInsertQueryMessageDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    NewInsertQueryMessage *pp = (NewInsertQueryMessage *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string NewInsertQueryMessageDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    NewInsertQueryMessage *pp = (NewInsertQueryMessage *)object; (void)pp;
    switch (field) {
        case 0: return ulong2string(pp->getDataSeq());
        default: return "";
    }
}

bool NewInsertQueryMessageDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    NewInsertQueryMessage *pp = (NewInsertQueryMessage *)object; (void)pp;
    switch (field) {
        case 0: pp->setDataSeq(string2ulong(value)); return true;
        default: return false;
    }
}

const char *NewInsertQueryMessageDescriptor::getFieldStructName(void *object, int field) const
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

void *NewInsertQueryMessageDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    NewInsertQueryMessage *pp = (NewInsertQueryMessage *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(NewInsertQueryResponseMessage);

NewInsertQueryResponseMessage::NewInsertQueryResponseMessage(const char *name, int kind) : NewMessage(name,kind)
{
    this->dataSeq_var = 0;
    childNode_arraysize = 0;
    this->childNode_var = 0;
}

NewInsertQueryResponseMessage::NewInsertQueryResponseMessage(const NewInsertQueryResponseMessage& other) : NewMessage()
{
    setName(other.getName());
    childNode_arraysize = 0;
    this->childNode_var = 0;
    operator=(other);
}

NewInsertQueryResponseMessage::~NewInsertQueryResponseMessage()
{
    delete [] childNode_var;
}

NewInsertQueryResponseMessage& NewInsertQueryResponseMessage::operator=(const NewInsertQueryResponseMessage& other)
{
    if (this==&other) return *this;
    NewMessage::operator=(other);
    this->dataSeq_var = other.dataSeq_var;
    delete [] this->childNode_var;
    this->childNode_var = (other.childNode_arraysize==0) ? NULL : new ::TransportAddress[other.childNode_arraysize];
    childNode_arraysize = other.childNode_arraysize;
    for (unsigned int i=0; i<childNode_arraysize; i++)
        this->childNode_var[i] = other.childNode_var[i];
    return *this;
}

void NewInsertQueryResponseMessage::parsimPack(cCommBuffer *b)
{
    NewMessage::parsimPack(b);
    doPacking(b,this->dataSeq_var);
    b->pack(childNode_arraysize);
    doPacking(b,this->childNode_var,childNode_arraysize);
}

void NewInsertQueryResponseMessage::parsimUnpack(cCommBuffer *b)
{
    NewMessage::parsimUnpack(b);
    doUnpacking(b,this->dataSeq_var);
    delete [] this->childNode_var;
    b->unpack(childNode_arraysize);
    if (childNode_arraysize==0) {
        this->childNode_var = 0;
    } else {
        this->childNode_var = new ::TransportAddress[childNode_arraysize];
        doUnpacking(b,this->childNode_var,childNode_arraysize);
    }
}

unsigned int NewInsertQueryResponseMessage::getDataSeq() const
{
    return dataSeq_var;
}

void NewInsertQueryResponseMessage::setDataSeq(unsigned int dataSeq_var)
{
    this->dataSeq_var = dataSeq_var;
}

void NewInsertQueryResponseMessage::setChildNodeArraySize(unsigned int size)
{
    ::TransportAddress *childNode_var2 = (size==0) ? NULL : new ::TransportAddress[size];
    unsigned int sz = childNode_arraysize < size ? childNode_arraysize : size;
    for (unsigned int i=0; i<sz; i++)
        childNode_var2[i] = this->childNode_var[i];
    childNode_arraysize = size;
    delete [] this->childNode_var;
    this->childNode_var = childNode_var2;
}

unsigned int NewInsertQueryResponseMessage::getChildNodeArraySize() const
{
    return childNode_arraysize;
}

TransportAddress& NewInsertQueryResponseMessage::getChildNode(unsigned int k)
{
    if (k>=childNode_arraysize) throw cRuntimeError("Array of size %d indexed by %d", childNode_arraysize, k);
    return childNode_var[k];
}

void NewInsertQueryResponseMessage::setChildNode(unsigned int k, const TransportAddress& childNode_var)
{
    if (k>=childNode_arraysize) throw cRuntimeError("Array of size %d indexed by %d", childNode_arraysize, k);
    this->childNode_var[k]=childNode_var;
}

class NewInsertQueryResponseMessageDescriptor : public cClassDescriptor
{
  public:
    NewInsertQueryResponseMessageDescriptor();
    virtual ~NewInsertQueryResponseMessageDescriptor();

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

Register_ClassDescriptor(NewInsertQueryResponseMessageDescriptor);

NewInsertQueryResponseMessageDescriptor::NewInsertQueryResponseMessageDescriptor() : cClassDescriptor("NewInsertQueryResponseMessage", "NewMessage")
{
}

NewInsertQueryResponseMessageDescriptor::~NewInsertQueryResponseMessageDescriptor()
{
}

bool NewInsertQueryResponseMessageDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<NewInsertQueryResponseMessage *>(obj)!=NULL;
}

const char *NewInsertQueryResponseMessageDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int NewInsertQueryResponseMessageDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 2+basedesc->getFieldCount(object) : 2;
}

unsigned int NewInsertQueryResponseMessageDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISARRAY | FD_ISCOMPOUND,
    };
    return (field>=0 && field<2) ? fieldTypeFlags[field] : 0;
}

const char *NewInsertQueryResponseMessageDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "dataSeq",
        "childNode",
    };
    return (field>=0 && field<2) ? fieldNames[field] : NULL;
}

int NewInsertQueryResponseMessageDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='d' && strcmp(fieldName, "dataSeq")==0) return base+0;
    if (fieldName[0]=='c' && strcmp(fieldName, "childNode")==0) return base+1;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *NewInsertQueryResponseMessageDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "unsigned int",
        "TransportAddress",
    };
    return (field>=0 && field<2) ? fieldTypeStrings[field] : NULL;
}

const char *NewInsertQueryResponseMessageDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int NewInsertQueryResponseMessageDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    NewInsertQueryResponseMessage *pp = (NewInsertQueryResponseMessage *)object; (void)pp;
    switch (field) {
        case 1: return pp->getChildNodeArraySize();
        default: return 0;
    }
}

std::string NewInsertQueryResponseMessageDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    NewInsertQueryResponseMessage *pp = (NewInsertQueryResponseMessage *)object; (void)pp;
    switch (field) {
        case 0: return ulong2string(pp->getDataSeq());
        case 1: {std::stringstream out; out << pp->getChildNode(i); return out.str();}
        default: return "";
    }
}

bool NewInsertQueryResponseMessageDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    NewInsertQueryResponseMessage *pp = (NewInsertQueryResponseMessage *)object; (void)pp;
    switch (field) {
        case 0: pp->setDataSeq(string2ulong(value)); return true;
        default: return false;
    }
}

const char *NewInsertQueryResponseMessageDescriptor::getFieldStructName(void *object, int field) const
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
    };
    return (field>=0 && field<2) ? fieldStructNames[field] : NULL;
}

void *NewInsertQueryResponseMessageDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    NewInsertQueryResponseMessage *pp = (NewInsertQueryResponseMessage *)object; (void)pp;
    switch (field) {
        case 1: return (void *)(&pp->getChildNode(i)); break;
        default: return NULL;
    }
}

Register_Class(NewInsertEvalMessage);

NewInsertEvalMessage::NewInsertEvalMessage(const char *name, int kind) : NewMessage(name,kind)
{
    this->dataSeq_var = 0;
}

NewInsertEvalMessage::NewInsertEvalMessage(const NewInsertEvalMessage& other) : NewMessage()
{
    setName(other.getName());
    operator=(other);
}

NewInsertEvalMessage::~NewInsertEvalMessage()
{
}

NewInsertEvalMessage& NewInsertEvalMessage::operator=(const NewInsertEvalMessage& other)
{
    if (this==&other) return *this;
    NewMessage::operator=(other);
    this->dataSeq_var = other.dataSeq_var;
    return *this;
}

void NewInsertEvalMessage::parsimPack(cCommBuffer *b)
{
    NewMessage::parsimPack(b);
    doPacking(b,this->dataSeq_var);
}

void NewInsertEvalMessage::parsimUnpack(cCommBuffer *b)
{
    NewMessage::parsimUnpack(b);
    doUnpacking(b,this->dataSeq_var);
}

unsigned int NewInsertEvalMessage::getDataSeq() const
{
    return dataSeq_var;
}

void NewInsertEvalMessage::setDataSeq(unsigned int dataSeq_var)
{
    this->dataSeq_var = dataSeq_var;
}

class NewInsertEvalMessageDescriptor : public cClassDescriptor
{
  public:
    NewInsertEvalMessageDescriptor();
    virtual ~NewInsertEvalMessageDescriptor();

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

Register_ClassDescriptor(NewInsertEvalMessageDescriptor);

NewInsertEvalMessageDescriptor::NewInsertEvalMessageDescriptor() : cClassDescriptor("NewInsertEvalMessage", "NewMessage")
{
}

NewInsertEvalMessageDescriptor::~NewInsertEvalMessageDescriptor()
{
}

bool NewInsertEvalMessageDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<NewInsertEvalMessage *>(obj)!=NULL;
}

const char *NewInsertEvalMessageDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int NewInsertEvalMessageDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount(object) : 1;
}

unsigned int NewInsertEvalMessageDescriptor::getFieldTypeFlags(void *object, int field) const
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

const char *NewInsertEvalMessageDescriptor::getFieldName(void *object, int field) const
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

int NewInsertEvalMessageDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='d' && strcmp(fieldName, "dataSeq")==0) return base+0;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *NewInsertEvalMessageDescriptor::getFieldTypeString(void *object, int field) const
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

const char *NewInsertEvalMessageDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int NewInsertEvalMessageDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    NewInsertEvalMessage *pp = (NewInsertEvalMessage *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string NewInsertEvalMessageDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    NewInsertEvalMessage *pp = (NewInsertEvalMessage *)object; (void)pp;
    switch (field) {
        case 0: return ulong2string(pp->getDataSeq());
        default: return "";
    }
}

bool NewInsertEvalMessageDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    NewInsertEvalMessage *pp = (NewInsertEvalMessage *)object; (void)pp;
    switch (field) {
        case 0: pp->setDataSeq(string2ulong(value)); return true;
        default: return false;
    }
}

const char *NewInsertEvalMessageDescriptor::getFieldStructName(void *object, int field) const
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

void *NewInsertEvalMessageDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    NewInsertEvalMessage *pp = (NewInsertEvalMessage *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(NewInsertEvalResponseMessage);

NewInsertEvalResponseMessage::NewInsertEvalResponseMessage(const char *name, int kind) : NewMessage(name,kind)
{
    this->dataSeq_var = 0;
}

NewInsertEvalResponseMessage::NewInsertEvalResponseMessage(const NewInsertEvalResponseMessage& other) : NewMessage()
{
    setName(other.getName());
    operator=(other);
}

NewInsertEvalResponseMessage::~NewInsertEvalResponseMessage()
{
}

NewInsertEvalResponseMessage& NewInsertEvalResponseMessage::operator=(const NewInsertEvalResponseMessage& other)
{
    if (this==&other) return *this;
    NewMessage::operator=(other);
    this->dataSeq_var = other.dataSeq_var;
    return *this;
}

void NewInsertEvalResponseMessage::parsimPack(cCommBuffer *b)
{
    NewMessage::parsimPack(b);
    doPacking(b,this->dataSeq_var);
}

void NewInsertEvalResponseMessage::parsimUnpack(cCommBuffer *b)
{
    NewMessage::parsimUnpack(b);
    doUnpacking(b,this->dataSeq_var);
}

unsigned int NewInsertEvalResponseMessage::getDataSeq() const
{
    return dataSeq_var;
}

void NewInsertEvalResponseMessage::setDataSeq(unsigned int dataSeq_var)
{
    this->dataSeq_var = dataSeq_var;
}

class NewInsertEvalResponseMessageDescriptor : public cClassDescriptor
{
  public:
    NewInsertEvalResponseMessageDescriptor();
    virtual ~NewInsertEvalResponseMessageDescriptor();

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

Register_ClassDescriptor(NewInsertEvalResponseMessageDescriptor);

NewInsertEvalResponseMessageDescriptor::NewInsertEvalResponseMessageDescriptor() : cClassDescriptor("NewInsertEvalResponseMessage", "NewMessage")
{
}

NewInsertEvalResponseMessageDescriptor::~NewInsertEvalResponseMessageDescriptor()
{
}

bool NewInsertEvalResponseMessageDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<NewInsertEvalResponseMessage *>(obj)!=NULL;
}

const char *NewInsertEvalResponseMessageDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int NewInsertEvalResponseMessageDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount(object) : 1;
}

unsigned int NewInsertEvalResponseMessageDescriptor::getFieldTypeFlags(void *object, int field) const
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

const char *NewInsertEvalResponseMessageDescriptor::getFieldName(void *object, int field) const
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

int NewInsertEvalResponseMessageDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='d' && strcmp(fieldName, "dataSeq")==0) return base+0;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *NewInsertEvalResponseMessageDescriptor::getFieldTypeString(void *object, int field) const
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

const char *NewInsertEvalResponseMessageDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int NewInsertEvalResponseMessageDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    NewInsertEvalResponseMessage *pp = (NewInsertEvalResponseMessage *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string NewInsertEvalResponseMessageDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    NewInsertEvalResponseMessage *pp = (NewInsertEvalResponseMessage *)object; (void)pp;
    switch (field) {
        case 0: return ulong2string(pp->getDataSeq());
        default: return "";
    }
}

bool NewInsertEvalResponseMessageDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    NewInsertEvalResponseMessage *pp = (NewInsertEvalResponseMessage *)object; (void)pp;
    switch (field) {
        case 0: pp->setDataSeq(string2ulong(value)); return true;
        default: return false;
    }
}

const char *NewInsertEvalResponseMessageDescriptor::getFieldStructName(void *object, int field) const
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

void *NewInsertEvalResponseMessageDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    NewInsertEvalResponseMessage *pp = (NewInsertEvalResponseMessage *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(NewInsertMessage);

NewInsertMessage::NewInsertMessage(const char *name, int kind) : NewMessage(name,kind)
{
    this->isChildNode_var = 0;
    this->dataSeq_var = 0;
    this->selectedDataSeq_var = 0;
}

NewInsertMessage::NewInsertMessage(const NewInsertMessage& other) : NewMessage()
{
    setName(other.getName());
    operator=(other);
}

NewInsertMessage::~NewInsertMessage()
{
}

NewInsertMessage& NewInsertMessage::operator=(const NewInsertMessage& other)
{
    if (this==&other) return *this;
    NewMessage::operator=(other);
    this->isChildNode_var = other.isChildNode_var;
    this->dataSeq_var = other.dataSeq_var;
    this->selectedNode_var = other.selectedNode_var;
    this->selectedDataSeq_var = other.selectedDataSeq_var;
    return *this;
}

void NewInsertMessage::parsimPack(cCommBuffer *b)
{
    NewMessage::parsimPack(b);
    doPacking(b,this->isChildNode_var);
    doPacking(b,this->dataSeq_var);
    doPacking(b,this->selectedNode_var);
    doPacking(b,this->selectedDataSeq_var);
}

void NewInsertMessage::parsimUnpack(cCommBuffer *b)
{
    NewMessage::parsimUnpack(b);
    doUnpacking(b,this->isChildNode_var);
    doUnpacking(b,this->dataSeq_var);
    doUnpacking(b,this->selectedNode_var);
    doUnpacking(b,this->selectedDataSeq_var);
}

bool NewInsertMessage::getIsChildNode() const
{
    return isChildNode_var;
}

void NewInsertMessage::setIsChildNode(bool isChildNode_var)
{
    this->isChildNode_var = isChildNode_var;
}

unsigned int NewInsertMessage::getDataSeq() const
{
    return dataSeq_var;
}

void NewInsertMessage::setDataSeq(unsigned int dataSeq_var)
{
    this->dataSeq_var = dataSeq_var;
}

TransportAddress& NewInsertMessage::getSelectedNode()
{
    return selectedNode_var;
}

void NewInsertMessage::setSelectedNode(const TransportAddress& selectedNode_var)
{
    this->selectedNode_var = selectedNode_var;
}

unsigned int NewInsertMessage::getSelectedDataSeq() const
{
    return selectedDataSeq_var;
}

void NewInsertMessage::setSelectedDataSeq(unsigned int selectedDataSeq_var)
{
    this->selectedDataSeq_var = selectedDataSeq_var;
}

class NewInsertMessageDescriptor : public cClassDescriptor
{
  public:
    NewInsertMessageDescriptor();
    virtual ~NewInsertMessageDescriptor();

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

Register_ClassDescriptor(NewInsertMessageDescriptor);

NewInsertMessageDescriptor::NewInsertMessageDescriptor() : cClassDescriptor("NewInsertMessage", "NewMessage")
{
}

NewInsertMessageDescriptor::~NewInsertMessageDescriptor()
{
}

bool NewInsertMessageDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<NewInsertMessage *>(obj)!=NULL;
}

const char *NewInsertMessageDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int NewInsertMessageDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 4+basedesc->getFieldCount(object) : 4;
}

unsigned int NewInsertMessageDescriptor::getFieldTypeFlags(void *object, int field) const
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

const char *NewInsertMessageDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "isChildNode",
        "dataSeq",
        "selectedNode",
        "selectedDataSeq",
    };
    return (field>=0 && field<4) ? fieldNames[field] : NULL;
}

int NewInsertMessageDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='i' && strcmp(fieldName, "isChildNode")==0) return base+0;
    if (fieldName[0]=='d' && strcmp(fieldName, "dataSeq")==0) return base+1;
    if (fieldName[0]=='s' && strcmp(fieldName, "selectedNode")==0) return base+2;
    if (fieldName[0]=='s' && strcmp(fieldName, "selectedDataSeq")==0) return base+3;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *NewInsertMessageDescriptor::getFieldTypeString(void *object, int field) const
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

const char *NewInsertMessageDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int NewInsertMessageDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    NewInsertMessage *pp = (NewInsertMessage *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string NewInsertMessageDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    NewInsertMessage *pp = (NewInsertMessage *)object; (void)pp;
    switch (field) {
        case 0: return bool2string(pp->getIsChildNode());
        case 1: return ulong2string(pp->getDataSeq());
        case 2: {std::stringstream out; out << pp->getSelectedNode(); return out.str();}
        case 3: return ulong2string(pp->getSelectedDataSeq());
        default: return "";
    }
}

bool NewInsertMessageDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    NewInsertMessage *pp = (NewInsertMessage *)object; (void)pp;
    switch (field) {
        case 0: pp->setIsChildNode(string2bool(value)); return true;
        case 1: pp->setDataSeq(string2ulong(value)); return true;
        case 3: pp->setSelectedDataSeq(string2ulong(value)); return true;
        default: return false;
    }
}

const char *NewInsertMessageDescriptor::getFieldStructName(void *object, int field) const
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

void *NewInsertMessageDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    NewInsertMessage *pp = (NewInsertMessage *)object; (void)pp;
    switch (field) {
        case 2: return (void *)(&pp->getSelectedNode()); break;
        default: return NULL;
    }
}

Register_Class(NewInsertResponseMessage);

NewInsertResponseMessage::NewInsertResponseMessage(const char *name, int kind) : NewMessage(name,kind)
{
    this->isChildNode_var = 0;
    this->dataSeq_var = 0;
}

NewInsertResponseMessage::NewInsertResponseMessage(const NewInsertResponseMessage& other) : NewMessage()
{
    setName(other.getName());
    operator=(other);
}

NewInsertResponseMessage::~NewInsertResponseMessage()
{
}

NewInsertResponseMessage& NewInsertResponseMessage::operator=(const NewInsertResponseMessage& other)
{
    if (this==&other) return *this;
    NewMessage::operator=(other);
    this->isChildNode_var = other.isChildNode_var;
    this->dataSeq_var = other.dataSeq_var;
    return *this;
}

void NewInsertResponseMessage::parsimPack(cCommBuffer *b)
{
    NewMessage::parsimPack(b);
    doPacking(b,this->isChildNode_var);
    doPacking(b,this->dataSeq_var);
}

void NewInsertResponseMessage::parsimUnpack(cCommBuffer *b)
{
    NewMessage::parsimUnpack(b);
    doUnpacking(b,this->isChildNode_var);
    doUnpacking(b,this->dataSeq_var);
}

bool NewInsertResponseMessage::getIsChildNode() const
{
    return isChildNode_var;
}

void NewInsertResponseMessage::setIsChildNode(bool isChildNode_var)
{
    this->isChildNode_var = isChildNode_var;
}

unsigned int NewInsertResponseMessage::getDataSeq() const
{
    return dataSeq_var;
}

void NewInsertResponseMessage::setDataSeq(unsigned int dataSeq_var)
{
    this->dataSeq_var = dataSeq_var;
}

class NewInsertResponseMessageDescriptor : public cClassDescriptor
{
  public:
    NewInsertResponseMessageDescriptor();
    virtual ~NewInsertResponseMessageDescriptor();

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

Register_ClassDescriptor(NewInsertResponseMessageDescriptor);

NewInsertResponseMessageDescriptor::NewInsertResponseMessageDescriptor() : cClassDescriptor("NewInsertResponseMessage", "NewMessage")
{
}

NewInsertResponseMessageDescriptor::~NewInsertResponseMessageDescriptor()
{
}

bool NewInsertResponseMessageDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<NewInsertResponseMessage *>(obj)!=NULL;
}

const char *NewInsertResponseMessageDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int NewInsertResponseMessageDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 2+basedesc->getFieldCount(object) : 2;
}

unsigned int NewInsertResponseMessageDescriptor::getFieldTypeFlags(void *object, int field) const
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

const char *NewInsertResponseMessageDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "isChildNode",
        "dataSeq",
    };
    return (field>=0 && field<2) ? fieldNames[field] : NULL;
}

int NewInsertResponseMessageDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='i' && strcmp(fieldName, "isChildNode")==0) return base+0;
    if (fieldName[0]=='d' && strcmp(fieldName, "dataSeq")==0) return base+1;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *NewInsertResponseMessageDescriptor::getFieldTypeString(void *object, int field) const
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

const char *NewInsertResponseMessageDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int NewInsertResponseMessageDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    NewInsertResponseMessage *pp = (NewInsertResponseMessage *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string NewInsertResponseMessageDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    NewInsertResponseMessage *pp = (NewInsertResponseMessage *)object; (void)pp;
    switch (field) {
        case 0: return bool2string(pp->getIsChildNode());
        case 1: return ulong2string(pp->getDataSeq());
        default: return "";
    }
}

bool NewInsertResponseMessageDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    NewInsertResponseMessage *pp = (NewInsertResponseMessage *)object; (void)pp;
    switch (field) {
        case 0: pp->setIsChildNode(string2bool(value)); return true;
        case 1: pp->setDataSeq(string2ulong(value)); return true;
        default: return false;
    }
}

const char *NewInsertResponseMessageDescriptor::getFieldStructName(void *object, int field) const
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

void *NewInsertResponseMessageDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    NewInsertResponseMessage *pp = (NewInsertResponseMessage *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(NewJoinSuccessMessage);

NewJoinSuccessMessage::NewJoinSuccessMessage(const char *name, int kind) : NewMessage(name,kind)
{
}

NewJoinSuccessMessage::NewJoinSuccessMessage(const NewJoinSuccessMessage& other) : NewMessage()
{
    setName(other.getName());
    operator=(other);
}

NewJoinSuccessMessage::~NewJoinSuccessMessage()
{
}

NewJoinSuccessMessage& NewJoinSuccessMessage::operator=(const NewJoinSuccessMessage& other)
{
    if (this==&other) return *this;
    NewMessage::operator=(other);
    return *this;
}

void NewJoinSuccessMessage::parsimPack(cCommBuffer *b)
{
    NewMessage::parsimPack(b);
}

void NewJoinSuccessMessage::parsimUnpack(cCommBuffer *b)
{
    NewMessage::parsimUnpack(b);
}

class NewJoinSuccessMessageDescriptor : public cClassDescriptor
{
  public:
    NewJoinSuccessMessageDescriptor();
    virtual ~NewJoinSuccessMessageDescriptor();

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

Register_ClassDescriptor(NewJoinSuccessMessageDescriptor);

NewJoinSuccessMessageDescriptor::NewJoinSuccessMessageDescriptor() : cClassDescriptor("NewJoinSuccessMessage", "NewMessage")
{
}

NewJoinSuccessMessageDescriptor::~NewJoinSuccessMessageDescriptor()
{
}

bool NewJoinSuccessMessageDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<NewJoinSuccessMessage *>(obj)!=NULL;
}

const char *NewJoinSuccessMessageDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int NewJoinSuccessMessageDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 0+basedesc->getFieldCount(object) : 0;
}

unsigned int NewJoinSuccessMessageDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    return 0;
}

const char *NewJoinSuccessMessageDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    return NULL;
}

int NewJoinSuccessMessageDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *NewJoinSuccessMessageDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    return NULL;
}

const char *NewJoinSuccessMessageDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int NewJoinSuccessMessageDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    NewJoinSuccessMessage *pp = (NewJoinSuccessMessage *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string NewJoinSuccessMessageDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    NewJoinSuccessMessage *pp = (NewJoinSuccessMessage *)object; (void)pp;
    switch (field) {
        default: return "";
    }
}

bool NewJoinSuccessMessageDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    NewJoinSuccessMessage *pp = (NewJoinSuccessMessage *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *NewJoinSuccessMessageDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    return NULL;
}

void *NewJoinSuccessMessageDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    NewJoinSuccessMessage *pp = (NewJoinSuccessMessage *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(NewStatisticMessage);

NewStatisticMessage::NewStatisticMessage(const char *name, int kind) : NewMessage(name,kind)
{
    this->dataSeq_var = 0;
    this->jumpNum_var = 0;
    this->dataTimeStamp_var = 0;
}

NewStatisticMessage::NewStatisticMessage(const NewStatisticMessage& other) : NewMessage()
{
    setName(other.getName());
    operator=(other);
}

NewStatisticMessage::~NewStatisticMessage()
{
}

NewStatisticMessage& NewStatisticMessage::operator=(const NewStatisticMessage& other)
{
    if (this==&other) return *this;
    NewMessage::operator=(other);
    this->dataSeq_var = other.dataSeq_var;
    this->jumpNum_var = other.jumpNum_var;
    this->dataTimeStamp_var = other.dataTimeStamp_var;
    return *this;
}

void NewStatisticMessage::parsimPack(cCommBuffer *b)
{
    NewMessage::parsimPack(b);
    doPacking(b,this->dataSeq_var);
    doPacking(b,this->jumpNum_var);
    doPacking(b,this->dataTimeStamp_var);
}

void NewStatisticMessage::parsimUnpack(cCommBuffer *b)
{
    NewMessage::parsimUnpack(b);
    doUnpacking(b,this->dataSeq_var);
    doUnpacking(b,this->jumpNum_var);
    doUnpacking(b,this->dataTimeStamp_var);
}

unsigned int NewStatisticMessage::getDataSeq() const
{
    return dataSeq_var;
}

void NewStatisticMessage::setDataSeq(unsigned int dataSeq_var)
{
    this->dataSeq_var = dataSeq_var;
}

unsigned int NewStatisticMessage::getJumpNum() const
{
    return jumpNum_var;
}

void NewStatisticMessage::setJumpNum(unsigned int jumpNum_var)
{
    this->jumpNum_var = jumpNum_var;
}

simtime_t NewStatisticMessage::getDataTimeStamp() const
{
    return dataTimeStamp_var;
}

void NewStatisticMessage::setDataTimeStamp(simtime_t dataTimeStamp_var)
{
    this->dataTimeStamp_var = dataTimeStamp_var;
}

class NewStatisticMessageDescriptor : public cClassDescriptor
{
  public:
    NewStatisticMessageDescriptor();
    virtual ~NewStatisticMessageDescriptor();

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

Register_ClassDescriptor(NewStatisticMessageDescriptor);

NewStatisticMessageDescriptor::NewStatisticMessageDescriptor() : cClassDescriptor("NewStatisticMessage", "NewMessage")
{
}

NewStatisticMessageDescriptor::~NewStatisticMessageDescriptor()
{
}

bool NewStatisticMessageDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<NewStatisticMessage *>(obj)!=NULL;
}

const char *NewStatisticMessageDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int NewStatisticMessageDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 3+basedesc->getFieldCount(object) : 3;
}

unsigned int NewStatisticMessageDescriptor::getFieldTypeFlags(void *object, int field) const
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

const char *NewStatisticMessageDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "dataSeq",
        "jumpNum",
        "dataTimeStamp",
    };
    return (field>=0 && field<3) ? fieldNames[field] : NULL;
}

int NewStatisticMessageDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='d' && strcmp(fieldName, "dataSeq")==0) return base+0;
    if (fieldName[0]=='j' && strcmp(fieldName, "jumpNum")==0) return base+1;
    if (fieldName[0]=='d' && strcmp(fieldName, "dataTimeStamp")==0) return base+2;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *NewStatisticMessageDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "unsigned int",
        "unsigned int",
        "simtime_t",
    };
    return (field>=0 && field<3) ? fieldTypeStrings[field] : NULL;
}

const char *NewStatisticMessageDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int NewStatisticMessageDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    NewStatisticMessage *pp = (NewStatisticMessage *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string NewStatisticMessageDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    NewStatisticMessage *pp = (NewStatisticMessage *)object; (void)pp;
    switch (field) {
        case 0: return ulong2string(pp->getDataSeq());
        case 1: return ulong2string(pp->getJumpNum());
        case 2: return double2string(pp->getDataTimeStamp());
        default: return "";
    }
}

bool NewStatisticMessageDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    NewStatisticMessage *pp = (NewStatisticMessage *)object; (void)pp;
    switch (field) {
        case 0: pp->setDataSeq(string2ulong(value)); return true;
        case 1: pp->setJumpNum(string2ulong(value)); return true;
        case 2: pp->setDataTimeStamp(string2double(value)); return true;
        default: return false;
    }
}

const char *NewStatisticMessageDescriptor::getFieldStructName(void *object, int field) const
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

void *NewStatisticMessageDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    NewStatisticMessage *pp = (NewStatisticMessage *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}


