#ifndef _DCacheDemoServer_H_
#define _DCacheDemoServer_H_

#include <iostream>
#include "servant/Application.h"

using namespace tars;

#include "servant/Communicator.h"
#include "Proxy.h"
using namespace DCache;

/**
 *
 **/
class DCacheDemoServer : public Application
{
public:
    /**
     *
     **/
    virtual ~DCacheDemoServer() {};

    /**
     *
     **/
    virtual void initialize();

    /**
     *
     **/
    virtual void destroyApp();
    bool test(const string& command, const string& params, string& result);
    bool help(const string& command, const string& params, string& result);
    bool SetKV(const string& command, const string& params, string& result);
    bool GetKV(const string& command, const string& params, string& result);
    bool DelKV(const string& command, const string& params, string& result);
    bool ListKV(const string& command, const string& params, string& result);
};

extern DCacheDemoServer g_app;

////////////////////////////////////////////
#endif
