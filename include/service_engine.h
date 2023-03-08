#ifndef __SERVICE_ENGINE_H
#define __SERVICE_ENGINE_H

#include <mysql.h>
#include <map>
#include "CustomMdSpi.h"
#include "CustomTradeSpi.h"
#include "ThostFtdcMdApi.h"
#include "ThostFtdcTraderApi.h"
#include "SimMdApi.h"
#include "SimTradeApi.h"
#include "convert.h"
#include <thread>
#include "base.h"
#include <signal.h>
#include <format>
#include "ini/ini.h"

class ServerCTAEngine {
private:
    //行情端参数 CTP
    TThostFtdcBrokerIDType pcCTPMdBrokerID;
    TThostFtdcInvestorIDType pcCTPMdUserID;
    TThostFtdcPasswordType pcCTPInvesterMdPassword;
    TThostFtdcAppIDType pcAppid;
    TThostFtdcAuthCodeType pcAuthCode;
    char pcCTPMdFrontAddr[28];
    //行情端参数 QTP
    TQdFtdcBrokerIDType pcQTPMdBrokerID;
    TQdFtdcUserIDType pcQTPMdUserID;
    TQdFtdcPasswordType pcQTPMdInvesterPassword;
    char pcQTPMdFrontAddr[28];
    //行情数据结构 CTP
    CThostFtdcMdApi* pCTPMdUserApi;
    CustomCTPMdSpi* pCTPMdUserSpi;
    //行情数据结构 QTP
    CQdFtdcMduserApi * pQTPMdUserApi;
    CustomQTPMdSpi * pQTPMdUserSpi;
    //交易端参数 CTP
    TThostFtdcBrokerIDType pcCTPTradeBrokerID;
    TThostFtdcUserIDType pcCTPTradeUserID;
    TThostFtdcPasswordType pcCTPInvesterTradePassword;
    char pcCTPTradeFrontAddr[28];
    //交易端参数 QTP
    TQdFtdcBrokerIDType pcQTPTradeBrokerID;
    TQdFtdcUserIDType pcQTPTradeUserID;
    TQdFtdcPasswordType pcQTPTradeInvesterPassword;
    char pcQTPTradeFrontAddr[28];
    //交易端数据结构 CTP
    CThostFtdcTraderApi* pCTPTradeUserApi;
    CustomCTPTradeSpi* pCTPTradeUserSpi;
    //交易端数据结构 QTP
    CQdpFtdcTraderApi * pQTPTradeUserApi;
    CustomQTPTradeSpi * pQTPTradeUserSpi;
    //数据库数据结构
    char pcMySQLIPAddr[16];    // ipv4 only
    char pcMySQLUsernm[15];
    char pcMySQLPasswd[20];
    char pcMysQLDBname[30];
    short iMySQLPort = 3306;   // default

    //行情数据结构 回测行情
    SimMdApi * pSimMdUserApi;
    SimMdSpi * pSimMdUserSpi;
    //交易数据结构 模拟交易
    SimTraderApi *pSimTradeUserApi;
    SimTradeSpi *pSimTradeUserSpi;

    //订阅数据结构
    std::unordered_map<std::string, char *> mSubscribeMap;  //key:期货代码，value:sid的vector
    std::unordered_map<std::string, BarManager> mBarManagerMap; //key:期货代码，value:Tick
    std::queue<Tick *> qTicks; // 插入Tick用于入库
    dict mExSymbol;
    std::map<int, int> mOrderMap;

    //入库相关结构
    MYSQL *mysql = nullptr;
    //Socket 相关结构
    SocketConn<0> *conn = nullptr;

    //其它内部结构
    int nSid = 1;
    int nOrderID = 0;
    int nRequestID = 0;
    MemoryPool_Event pool;

    /* 内部函数 */
    // 启动相关
    inline void setParam(); //用于构造函数中参数初始化，以便将参数传给底层
    template <int flag> inline void getPUserApi(); //创建行情交易Api
    template <int flag> inline void getPUserSpi(); //创建行情交易Spi
    template <int flag> inline void createPUserSpi(); //创建行情实例
    template <int flag> inline void connectQuote(); //用于连接行情
    void time_manager(); // 时间管理大师
    //此层调用底层
    inline int SubscribeMarketData(std::string &, dict&); //收到订阅
    inline int receiveOrderData(std::string &, dict&); //向底层请求下单
    inline void reSubMarketData(const int flag); // 登陆重新订阅
    void queryContracts(std::string &);

public:
    //外部参数
    std::binary_semaphore CTPLogin;
    std::binary_semaphore QTPLogin;
    bool CTPonTrading = false;
    bool QTPonTrading = false;

    //初始化相关
    ServerCTAEngine();
    void start();
    //底层调用此层
    template <typename T> inline void getTick(T *);
    //底层调用此层CTP
    void getOrder(CThostFtdcOrderField *); //底层推出order，此层推入端口
    void getTrade(CThostFtdcTradeField *); //底层推出trade，此层推入端口
    //底层调用此层QTP
    void getOrder(CQdpFtdcOrderField *); //底层推出order，此层推入端口
    void getTrade(CQdpFtdcTradeField *); //底层推出trade，此层推入端口
    //分流
    inline bool subMarketDistribution(const char *, const char *) noexcept;
    inline void dataDistribution(Tick*); //分发给每个策略和入库
    inline void sendData(char method, char * data,size_t length, const int& sid); //分发给策略
    void saveBar(); //入库
    inline void onSaveBar(Bar &); // 入库回调
    //接收请求
    void recvData();

    //结束
    template <int flag> inline void disconnectQuote();
    ~ServerCTAEngine() noexcept;
};

template void ServerCTAEngine::getTick(CThostFtdcDepthMarketDataField*);
template void ServerCTAEngine::getTick(CQdFtdcDepthMarketDataField *);
#endif //SERVICE_ENGINE_H