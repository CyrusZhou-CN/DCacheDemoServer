#ifndef _DCacheDemoServantImp_H_
#define _DCacheDemoServantImp_H_

#include "servant/Application.h"
#include "DCacheDemoServant.h"

/**
 *
 *
 */
class DCacheDemoServantImp : public DCacheDemo::DCacheDemoServant
{
public:
    /**
     *
     */
    virtual ~DCacheDemoServantImp() {}

    /**
     *
     */
    virtual void initialize();

    /**
     *
     */
    virtual void destroy();

    /**
     *
     */
    virtual int test(tars::TarsCurrentPtr current);
    virtual int SetKV(const string& kv_key,const string& kv_value,tars::TarsCurrentPtr current);
    virtual int GetKV(const string& kv_key, tars::TarsCurrentPtr current);
    virtual int DelKV(const string& kv_key, tars::TarsCurrentPtr current);
    virtual int ListKV(tars::TarsCurrentPtr current);

};
/////////////////////////////////////////////////////
#endif
