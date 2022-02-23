#include "DCacheDemoServantImp.h"
#include "servant/Application.h"
#include "DCacheDemoServer.h"
using namespace std;

//////////////////////////////////////////////////////
void DCacheDemoServantImp::initialize()
{
    //initialize servant here:
    //...
}

//////////////////////////////////////////////////////
void DCacheDemoServantImp::destroy()
{
    //destroy servant here:
    //...
}

int DCacheDemoServantImp::test(tars::TarsCurrentPtr current)
{
    TLOGDEBUG("[DCacheDemoServantImp::test]"
              << "current:" << current << endl);
    DCacheDemoServer dcacheDemoServer;
    string result{};
    dcacheDemoServer.test("test", "", result);
    TLOGDEBUG("[DCacheDemoServantImp::test]"
              << "result:" << result << endl);

    return 0;
}
int DCacheDemoServantImp::SetKV(const string& kv_key,const string& kv_value, tars::TarsCurrentPtr current)
{    
    TLOGDEBUG("[DCacheDemoServantImp::SetKV]"
              << "current:" << current << endl);
    DCacheDemoServer dcacheDemoServer;
    string result{};
    dcacheDemoServer.SetKV("setkv", kv_key + ":" + kv_value, result);
    TLOGDEBUG("[DCacheDemoServantImp::SetKV]"
              << "result:" << result << endl);

    return 0;
}
int DCacheDemoServantImp::GetKV(const string& kv_key, tars::TarsCurrentPtr current)
{
    return 0;
}
int DCacheDemoServantImp::DelKV(const string& kv_key, tars::TarsCurrentPtr current)
{
    return 0;
}
int DCacheDemoServantImp::ListKV(tars::TarsCurrentPtr current)
{
    return 0;
}

