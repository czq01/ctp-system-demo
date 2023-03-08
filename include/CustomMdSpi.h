# ifndef __MARKETDATA_SPI_
# define __MARKETDATA_SPI_
// ---- 派生的行情类 ---- //
#include <vector>
#include <iostream>
#include <cstring>
#include <functional>
#include "ThostFtdcMdApi.h"
#include "QdFtdcMdApi.h"
#include "SimMdApi.h"

class ServerCTAEngine;
class CustomCTPMdSpi : public CThostFtdcMdSpi
// class CustomCTPMdSpi : public SimMdApi
{   // ---- 继承自CTP父类的回调接口并实现 ---- //
public:
    CThostFtdcMdApi *g_pMdUserApi;             // 行情指针
    char gMdFrontAddr[50];                        // 模拟行情前置地址
    TThostFtdcBrokerIDType pcBrokerID;          // 模拟经纪商代码
    TThostFtdcUserIDType pcUserID;      // 投资者账户
    TThostFtdcInvestorIDType pcInvestorID;      // 投资者代码
    TThostFtdcPasswordType pcCTPMdInvesterPassword;  // 投资者密码
    char **g_pInstrumentID;  // 行情合约代码列表，中、上、大、郑交易所各选一种
    int instrumentNum;  // 行情合约订阅数量
    // engine指针
    ServerCTAEngine *fp = nullptr;
    CustomCTPMdSpi(CThostFtdcMdApi *g_pMdUserApi, char gMdFrontAddr[],
                TThostFtdcBrokerIDType pcBrokerID,
                TThostFtdcUserIDType gUserID,
                TThostFtdcPasswordType pcCTPTradeInvesterPassword,
                ServerCTAEngine *p);

    ///当客户端与交易后台建立起通信连接时（还未登录前），该方法被调用。
    void OnFrontConnected();

    ///当客户端与交易后台通信连接断开时，该方法被调用。当发生这个情况后，API会自动重新连接，客户端可不做处理。
    ///@param nReason 错误原因
    ///        0x1001 网络读失败
    ///        0x1002 网络写失败
    ///        0x2001 接收心跳超时
    ///        0x2002 发送心跳失败
    ///        0x2003 收到错误报文
    void OnFrontDisconnected(int nReason);

    ///心跳超时警告。当长时间未收到报文时，该方法被调用。
    ///@param nTimeLapse 距离上次接收报文的时间
    void OnHeartBeatWarning(int nTimeLapse);

    ///登录请求响应
    void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin,
                        CThostFtdcRspInfoField *pRspInfo, int nRequestID,
                        bool bIsLast);

    ///登出请求响应
    void OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout,
                         CThostFtdcRspInfoField *pRspInfo, int nRequestID,
                         bool bIsLast);

    ///错误应答
    void OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID,
                    bool bIsLast);

    ///订阅行情应答
    void OnRspSubMarketData(
            CThostFtdcSpecificInstrumentField *pSpecificInstrument,
            CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    ///取消订阅行情应答
    void OnRspUnSubMarketData(
            CThostFtdcSpecificInstrumentField *pSpecificInstrument,
            CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    ///订阅询价应答
    void OnRspSubForQuoteRsp(
            CThostFtdcSpecificInstrumentField *pSpecificInstrument,
            CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    ///取消订阅询价应答
    void OnRspUnSubForQuoteRsp(
            CThostFtdcSpecificInstrumentField *pSpecificInstrument,
            CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    ///深度行情通知
    void OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData);

    ///询价通知
    void OnRtnForQuoteRsp(CThostFtdcForQuoteRspField *pForQuoteRsp);
};

class CustomQTPMdSpi : public CQdFtdcMduserSpi {
    // ---- 继承自CTP父类的回调接口并实现 ---- //
public:
    CQdFtdcMduserApi *g_pMdUserApi;             // 行情指针
    char gMdFrontAddr[50];                        // 模拟行情前置地址
    TQdFtdcBrokerIDType pcBrokerID;          // 模拟经纪商代码
    TQdFtdcUserIDType gInvestorID;      // 投资者账户名
    TQdFtdcPasswordType pcQTPMdInvesterPassword;  // 投资者密码

    // engine指针
    ServerCTAEngine *fp = nullptr;
    CustomQTPMdSpi(CQdFtdcMduserApi *g_pMdUserApi,
                char gMdFrontAddr[],
                TQdFtdcBrokerIDType pcBrokerID,
                TQdFtdcUserIDType gUserID,
                TQdFtdcPasswordType pcQTPMdInvesterPassword,
                ServerCTAEngine *p);

    ///当客户端与交易后台建立起通信连接时（还未登录前），该方法被调用。
    void OnFrontConnected();

    ///当客户端与交易后台通信连接断开时，该方法被调用。当发生这个情况后，API会自动重新连接，客户端可不做处理。
    ///@param nReason 错误原因
    ///        0x1001 网络读失败
    ///        0x1002 网络写失败
    ///        0x2001 接收心跳超时
    ///        0x2002 发送心跳失败
    ///        0x2003 收到错误报文
    void OnFrontDisconnected(int nReason);

    ///心跳超时警告。当长时间未收到报文时，该方法被调用。
    ///@param nTimeLapse 距离上次接收报文的时间
    void OnHeartBeatWarning(int nTimeLapse);

    ///登录请求响应
    void OnRspUserLogin(CQdFtdcRspUserLoginField *pRspUserLogin,
                        CQdFtdcRspInfoField *pRspInfo, int nRequestID,
                        bool bIsLast);

    ///登出请求响应
    void OnRspUserLogout(CQdFtdcRspUserLogoutField *pUserLogout,
                         CQdFtdcRspInfoField *pRspInfo, int nRequestID,
                         bool bIsLast);

    ///错误应答
    void OnRspError(CQdFtdcRspInfoField *pRspInfo, int nRequestID,
                    bool bIsLast);

    ///订阅行情应答
    void OnRspSubMarketData(
            CQdFtdcSpecificInstrumentField *pSpecificInstrument,
            CQdFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    ///取消订阅行情应答
    void OnRspUnSubMarketData(
            CQdFtdcSpecificInstrumentField *pSpecificInstrument,
            CQdFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    ///订阅询价应答
    void OnRspSubForQuoteRsp(
            CQdFtdcSpecificInstrumentField *pSpecificInstrument,
            CQdFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    ///取消订阅询价应答
    void OnRspUnSubForQuoteRsp(
            CQdFtdcSpecificInstrumentField *pSpecificInstrument,
            CQdFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    ///深度行情通知
    void OnRtnDepthMarketData(CQdFtdcDepthMarketDataField *pDepthMarketData);
};

// ------------------------------------------
// BLOCK       backtesting
// ------------------------------------------

class CustomSimMdSpi : public SimMdSpi {   // ---- 继承自Sim父类的回调接口并实现 ---- //
public:
    CThostFtdcMdApi *g_pMdUserApi;             // 行情指针
    char gMdFrontAddr[50];                        // 模拟行情前置地址
    TThostFtdcBrokerIDType pcBrokerID;          // 模拟经纪商代码
    TThostFtdcUserIDType pcUserID;      // 投资者账户
    TThostFtdcInvestorIDType pcInvestorID;      // 投资者代码
    TThostFtdcPasswordType pcCTPMdInvesterPassword;  // 投资者密码
    char **g_pInstrumentID;  // 行情合约代码列表，中、上、大、郑交易所各选一种
    int instrumentNum;  // 行情合约订阅数量
    // engine指针
    ServerCTAEngine *fp = nullptr;
    CustomSimMdSpi(ServerCTAEngine *p);

    ///当客户端与交易后台建立起通信连接时（还未登录前），该方法被调用。
    void OnFrontConnected();

    ///当客户端与交易后台通信连接断开时，该方法被调用。当发生这个情况后，API会自动重新连接，客户端可不做处理。
    ///@param nReason 错误原因
    ///        0x1001 网络读失败
    ///        0x1002 网络写失败
    ///        0x2001 接收心跳超时
    ///        0x2002 发送心跳失败
    ///        0x2003 收到错误报文
    void OnFrontDisconnected(int nReason);

    ///错误应答
    void OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID,
                    bool bIsLast);

    ///订阅行情应答
    void OnRspSubMarketData(
            CThostFtdcSpecificInstrumentField *pSpecificInstrument,
            CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    ///取消订阅行情应答
    void OnRspUnSubMarketData(
            CThostFtdcSpecificInstrumentField *pSpecificInstrument,
            CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    ///深度行情通知
    void OnRtnDepthMarketData(Tick *pDepthMarketData, const int& sid);
};

# endif