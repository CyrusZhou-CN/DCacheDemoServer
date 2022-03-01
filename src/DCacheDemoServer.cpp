#include "DCacheDemoServer.h"
#include "DCacheDemoServantImp.h"

using namespace std;

DCacheDemoServer g_app;
Communicator comm;
ProxyPrx prx;
string locator = "tars.tarsregistry.QueryObj@tcp -h 7.1.0.3 -p 17890"; // 更换为实际地址
string module_name="";
string app_name="";
/////////////////////////////////////////////////////////////////
void
DCacheDemoServer::initialize()
{
    //initialize application here:
    //...

    addServant<DCacheDemoServantImp>(ServerConfig::Application + "." + ServerConfig::ServerName + ".DCacheDemoServantObj");
    
    addConfig("DCacheDemoServer.conf");
    
    TC_Config conf;
    conf.parseFile(ServerConfig::BasePath + "DCacheDemoServer.conf");
    TLOG_DEBUG("KValueModuleName:"<< conf.get("/root<KValueModuleName>") << endl);
    module_name = conf.get("/root<KValueModuleName>");
    app_name = conf.get("/root<AppName>");

    TARS_ADD_ADMIN_CMD_NORMAL("help", DCacheDemoServer::help);
    TARS_ADD_ADMIN_CMD_NORMAL("test", DCacheDemoServer::test);
    TARS_ADD_ADMIN_CMD_NORMAL("setkv", DCacheDemoServer::SetKV);
    TARS_ADD_ADMIN_CMD_NORMAL("getkv", DCacheDemoServer::GetKV);    
    TARS_ADD_ADMIN_CMD_NORMAL("delkv", DCacheDemoServer::DelKV);
    TARS_ADD_ADMIN_CMD_NORMAL("listkv", DCacheDemoServer::ListKV);

    comm.setProperty("locator", locator);
    comm.stringToProxy("DCache."+ app_name +"ProxyServer.ProxyObj", prx); // 更换为实际的proxy servant
}
/////////////////////////////////////////////////////////////////
void
DCacheDemoServer::destroyApp()
{
    //destroy application here:
    //...
}


bool DCacheDemoServer::SetKV(const string &command, const string &params, string &result)
{
    TLOGDEBUG("[DCacheDemoServer::SetKV]"
              << "module_name:" << module_name << ";command:" << command << ";params:" << params << endl);
    size_t d = params.find(":");
    string key = params.substr(0, d);
    string value = params.substr(d, params.length());
    // 写数据
    SetKVReq setreq;
    setreq.moduleName = module_name;
    setreq.data.keyItem = key;
    setreq.data.value = value;
    setreq.data.version = 0;
    setreq.data.dirty = false;
    setreq.data.expireTimeSecond = 0;
    TLOGDEBUG("[DCacheDemoServer::SetKV]"
              << "写入" + key + "数据:" + value + " |" << setreq << endl);
    auto ret = prx->setKV(setreq);
    if (ret != ET_SUCC)
    {
        result = "写入" + key + "数据:" + value + " 出错|" + to_string(ret);
        TLOGERROR("[DCacheDemoServer::SetKV]"
                  << "setKV error|" << ret << endl);
        return false;
    }
    result = "写入" + key + "数据:" + value +"完成\n";
    return true;
}
bool DCacheDemoServer::GetKV(const string &command, const string &params, string &result)
{
    TLOGDEBUG("[DCacheDemoServer::GetKV]"
              << "module_name:" << module_name << ";command:" << command << ";params:" << params << endl);
    // 读数据
    GetKVReq getreq;
    getreq.moduleName = module_name;
    getreq.keyItem = params;

    GetKVRsp getrsp;

    TLOGDEBUG("[DCacheDemoServer::test]"
              << "读取" + params + "数据:" << getreq << endl);
    auto ret = prx->getKV(getreq, getrsp);
    if (ret != ET_SUCC)
    {
        result = "读取" + params + "数据 出错 |" + to_string(ret);
        TLOGERROR("[DCacheDemoServer::GetKV]"
                  << "getKV error|" << ret << endl);
        return false;
    }
    result += "读取" + params + "数据:" + getrsp.value + "\n";
    return true;
}
bool DCacheDemoServer::DelKV(const string &command, const string &params, string &result)
{
    TLOGDEBUG("[DCacheDemoServer::DelKV]"
              << "module_name:" << module_name << ";command:" << command << ";params:" << params << endl);
    // 删除数据
    try
    {
        RemoveKVReq remakeKVReq;
        KeyInfo keyinfo;
        keyinfo.keyItem = params;
        remakeKVReq.moduleName = module_name;
        remakeKVReq.keyInfo = keyinfo;
        auto ret = prx->delKV(remakeKVReq);
        if (ret != ET_SUCC)
        {
            result += "删除" + params + "数据出错 |" + to_string(ret);
            TLOGERROR("[DCacheDemoServer::DelKV]"
                    << "getKV error|" << ret << endl);
            return false;
        }
        result += "删除" + params + "数据完成\n";
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return false;
    }
    return true;
}
bool DCacheDemoServer::ListKV(const string &command, const string &params, string &result)
{
    TLOGDEBUG("[DCacheDemoServer::ListKV]"
              << "module_name:" << module_name << ";command:" << command << ";params:" << params << endl);
    // 获取所有key
    GetAllKeysReq getAllKeysReq;
    getAllKeysReq.moduleName = module_name;
    getAllKeysReq.index = 0;
    getAllKeysReq.count = 1000;
    getAllKeysReq.idcSpecified = "Test";
    GetAllKeysRsp getAllKeysRsp;
    auto ret = prx->getAllKeys(getAllKeysReq, getAllKeysRsp);

    if (ret != ET_SUCC)
    {
        result += "获取前1000 key出错 |" + ret;
        TLOGERROR("[DCacheDemoServer::DelKV]"
                  << "getKV error|" << ret << endl);
        return false;
    }
    result += "key 列表\n";
    for (size_t i = 0; i < getAllKeysRsp.keys.size(); i++)
    {
        result += getAllKeysRsp.keys[i] + "\n";
    }
    result += "获取前1000 key完成\n";
    return true;
}
bool DCacheDemoServer::test(const string &command, const string &params, string &result)
{
    TLOGDEBUG("[DCacheDemoServer::test]"
              << "module_name:" << module_name << ";command:" << command << ";params:" << params << endl);

    // 写数据
    SetKVReq setreq;
    setreq.moduleName = module_name;
    setreq.data.keyItem = "test_key";
    setreq.data.value = "test_value";
    setreq.data.version = 0;
    setreq.data.dirty = false;
    setreq.data.expireTimeSecond = 0;
    TLOGDEBUG("[DCacheDemoServer::test]"
              << "写数据:" << setreq << endl);
    auto ret = prx->setKV(setreq);
    if (ret != ET_SUCC)
    {
        result = "setKV error|" + ret;
        TLOGERROR("[DCacheDemoServer::test]"
                  << "setKV error|" << ret << endl);
        return false;
    }
    // 读数据
    GetKVReq getreq;
    getreq.moduleName = module_name;
    getreq.keyItem = "test_key";

    GetKVRsp getrsp;

    TLOGDEBUG("[DCacheDemoServer::test]"
              << "读数据:" << getreq << endl);
    ret = prx->getKV(getreq, getrsp);
    if (ret != ET_SUCC)
    {
        result = "getKV error|" + ret;
        TLOGERROR("[DCacheDemoServer::test]"
                  << "getKV error|" << ret << endl);
        return false;
    }
    result += "读数据\n";
    result += "getKV :" + getrsp.value + "\n";
    // 批量写
    SetKVBatchReq set_kv_batch_req;
    set_kv_batch_req.moduleName = module_name;
    for (int i = 1; i < 10; ++i)
    {
        SSetKeyValue val;
        val.keyItem = to_string(i);
        val.value = "kv_batch" + to_string(i);
        val.version = 0;
        val.dirty = false;
        val.expireTimeSecond = 0;
        set_kv_batch_req.data.emplace_back(val);
    }

    SetKVBatchRsp set_kv_batch_rsp;

    TLOGDEBUG("[DCacheDemoServer::test]"
              << "批量写:" << set_kv_batch_req << endl);
    ret = prx->setKVBatch(set_kv_batch_req, set_kv_batch_rsp);
    if (ret != ET_SUCC)
    {
        result = "setKVBatch error|" + ret;
        TLOGERROR("[DCacheDemoServer::test]"
                  << "setKVBatch error|" << ret << endl);
        return false;
    }

    // 批量读
    GetKVBatchReq get_kv_batch_req;
    get_kv_batch_req.moduleName = module_name;
    for (int i = 1; i < 10; ++i)
    {
        get_kv_batch_req.keys.emplace_back(to_string(i));
    }

    GetKVBatchRsp get_kv_batch_rsp;
    TLOGDEBUG("[DCacheDemoServer::test]"
              << "批量读:" << get_kv_batch_req << endl);
    ret = prx->getKVBatch(get_kv_batch_req, get_kv_batch_rsp);
    if (ret != ET_SUCC)
    {
        result = "getKVBatch error|" + ret;
        TLOGERROR("[DCacheDemoServer::test]"
                  << "getKVBatch error|" << ret << endl);
        return false;
    }
    result += "批量读数据\n";
    result += "getKVBatch :\n";
    for (size_t i = 0; i < get_kv_batch_rsp.values.size(); i++)
    {
        result += get_kv_batch_rsp.values[i].value + "\n";
    }
    result += "读数据完成\n";
    return true;
}

bool DCacheDemoServer::help(const string &command, const string &params, string &result)
{
    result = "help: 显示Server的状态信息\n";
    result += "test: 测试KValue读写\n";
    result += "listkv: KValue 获取前1000 key列表\n";
    result += "setkv: KValue 写入操作(命令格式：setkv key:value)\n";
    result += "getkv: KValue 读取操作(命令格式：getkv key)\n";
    result += "delkv: KValue 删除操作(命令格式：delkv key)\n";

    return true;
}
/////////////////////////////////////////////////////////////////
int
main(int argc, char* argv[])
{
    try
    {
        g_app.main(argc, argv);
        g_app.waitForShutdown();
    }
    catch (std::exception& e)
    {
        cerr << "std::exception:" << e.what() << std::endl;
    }
    catch (...)
    {
        cerr << "unknown exception." << std::endl;
    }
    return -1;
}
/////////////////////////////////////////////////////////////////
