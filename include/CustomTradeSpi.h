#pragma once
// ---- 派生的交易类 ---- //
#ifndef __TRADE_SPI_
#define __TRADE_SPI_
#include "ThostFtdcTraderApi.h"
#include "QdpFtdcTraderApi.h"
#include "QdFtdcUserApiDataType.h"
#include "SimTradeApi.h"
#include <iostream>
#include <ctime>
#include <thread>
#include <chrono>
#include <cstdio>
#include <process.h>

class ServerCTAEngine;

class CustomCTPTradeSpi : public CThostFtdcTraderSpi
{
// ---- ctp_api部分回调接口 ---- //
public:
    CThostFtdcTraderApi *g_pTradeUserApi;                    // 交易指针
    char pcCTPTradeFrontAddr[50];                 // 交易前置地址  -- 国元次席
    TThostFtdcBrokerIDType pcBrokerID;                         // 模拟经纪商代码   中信
    TThostFtdcUserIDType pcInvestorID;                         // 投资者账户名
    TThostFtdcInvestorIDType pUserID;                         // 投资者账户名
    TThostFtdcPasswordType pcCTPTradeInvesterPassword;                     // 投资者密码
    TThostFtdcAppIDType appid ;           // 用户产品信息
    TThostFtdcAuthCodeType authcode;              //
    ServerCTAEngine *fp;
    // 会话参数
    TThostFtdcFrontIDType	trade_front_id;	//前置编号
    TThostFtdcSessionIDType	session_id;	//会话编号
    TThostFtdcOrderRefType	order_ref;	//报单引用
    CustomCTPTradeSpi(CThostFtdcTraderApi *g_pTradeUserApi,
                   TThostFtdcBrokerIDType BrokerID,
                   TThostFtdcInvestorIDType UserID,
                   TThostFtdcPasswordType QTPTradeInvesterPassword,
                   TThostFtdcAppIDType Appid,
                   TThostFtdcAuthCodeType authCode,
                   char pcCTPTradeFrontAddr[],
                   ServerCTAEngine *p);

    ///当客户端与交易后台建立起通信连接时（还未登录前），该方法被调用。
    void OnFrontConnected();

    ///客户端认证响应
    void OnRspAuthenticate(CThostFtdcRspAuthenticateField *pRspAuthenticateField, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    ///登录请求响应
    void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    ///错误应答
    void OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    ///当客户端与交易后台通信连接断开时，该方法被调用。当发生这个情况后，API会自动重新连接，客户端可不做处理。
    void OnFrontDisconnected(int nReason);

    ///心跳超时警告。当长时间未收到报文时，该方法被调用。
    void OnHeartBeatWarning(int nTimeLapse);

    ///登出请求响应
    void OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    ///投资者结算结果确认响应
    void OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    ///请求查询合约响应
    void OnRspQryInstrument(CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    ///请求查询资金账户响应
    void OnRspQryTradingAccount(CThostFtdcTradingAccountField *pTradingAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);


    ///请求查询投资者持仓响应
    void OnRspQryInvestorPosition(CThostFtdcInvestorPositionField *pInvestorPosition, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    ///报单录入请求响应
    void OnRspOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    ///报单操作请求响应
    void OnRspOrderAction(CThostFtdcInputOrderActionField *pInputOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    ///报单通知
    void OnRtnOrder(CThostFtdcOrderField *pOrder);

    ///成交通知
    void OnRtnTrade(CThostFtdcTradeField *pTrade);

// ---- 自定义函数 ---- //
public:
    bool loginFlag; // 登陆成功的标识

    void reqOrderInsert(
        TThostFtdcInstrumentIDType instrumentID,
        TThostFtdcOffsetFlagType ocFlag,
        TThostFtdcVolumeType volume,
        TThostFtdcDirectionType direction
        ); // 个性化报单录入，外部调用

    // void SubmitUserSystemInfo();

    void CusreqOrderInsert(
        TThostFtdcInstrumentIDType instrumentID,
        TThostFtdcOffsetFlagType ocflag,
        TThostFtdcVolumeType volume,
        TThostFtdcDirectionType direction,
        TThostFtdcPriceType limitprice,
        int orderid);// 个性化报单录入，外部调用

    void reqQueryInvestorPosition(TThostFtdcInstrumentIDType instrumentID); // 请求查询投资者持仓

private:
    int ReqAuthenticate(CThostFtdcReqAuthenticateField *pReqAuthenticateField, int nRequestID);
    void reqUserLogin(); // 登录请求
    void reqUserLogout(); // 登出请求
    void reqSettlementInfoConfirm(); // 投资者结果确认
    void reqQueryInstrument(TThostFtdcInstrumentIDType g_pTradeInstrumentID); // 请求查询合约
    void reqQueryTradingAccount(); // 请求查询资金帐户
    void reqOrderInsert(TThostFtdcInstrumentIDType g_pTradeInstrumentID, TThostFtdcDirectionType gTradeDirection, TThostFtdcPriceType gLimitPrice); // 请求报单录入
    void reqOrderAction(CThostFtdcOrderField *pOrder); // 请求报单操作
    bool isErrorRspInfo(CThostFtdcRspInfoField *pRspInfo); // 是否收到错误信息
};

class CustomQTPTradeSpi : public CQdpFtdcTraderSpi
{
// ---- ctp_api部分回调接口 ---- //
public:
    CQdpFtdcTraderApi *g_pTradeUserApi;                    // 交易指针
    char pcCTPTradeFrontAddr[28];                 // 交易前置地址  -- 国元次席
    TQdFtdcBrokerIDType pcBrokerID;                         // 模拟经纪商代码   中信
    TQdpFtdcInvestorIDType gInvestorID;                         // 投资者账户名
    TQdpFtdcUserIDType gUserID;                         // 投资者账户名
    TQdFtdcPasswordType pcQTPTradeInvesterPassword;                     // 投资者密码
    TQdFtdcAuthCodeType authcode;              //
    // 会话参数
    TQdFtdcFrontIDType trade_front_id;	//前置编号
    TQdFtdcSessionIDType session_id;	//会话编号
    TQdpFtdcCustomType order_ref;	//报单引用
    ServerCTAEngine * fp = nullptr;
    CustomQTPTradeSpi(CQdpFtdcTraderApi *g_pTradeUserApi,
                   TQdFtdcBrokerIDType pcBrokerID,
                   TQdpFtdcInvestorIDType gUserID,
                   TQdpFtdcPasswordType pcQTPMdInvesterPassword,
                   char pcCTPTradeFrontAddr[],
                   ServerCTAEngine *p);

    ///当客户端与交易后台建立起通信连接时（还未登录前），该方法被调用。
    void OnFrontConnected();

    ///登录请求响应
    void OnRspUserLogin(CQdpFtdcRspUserLoginField *pRspUserLogin, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    ///错误应答
    void OnRspError(CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    ///当客户端与交易后台通信连接断开时，该方法被调用。当发生这个情况后，API会自动重新连接，客户端可不做处理。
    void OnFrontDisconnected(int nReason);

    ///心跳超时警告。当长时间未收到报文时，该方法被调用。
    void OnHeartBeatWarning(int nTimeLapse);

    ///登出请求响应
    void OnRspUserLogout(CQdpFtdcRspUserLogoutField *pRspUserLogout, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    ///请求查询合约响应
    void OnRspQryInstrument(CQdpFtdcRspInstrumentField *pRspInstrument, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    ///请求查询投资者持仓响应
    void OnRspQryInvestorPosition(CQdpFtdcRspInvestorPositionField *pRspInvestorPosition, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    ///报单录入请求响应
    void OnRspOrderInsert(CQdpFtdcInputOrderField *pInputOrder, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    ///报单操作请求响应
    void OnRspOrderAction(CQdpFtdcOrderActionField *pOrderAction, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    ///请求查询资金账户响应
	void OnRspQryInvestorAccount(CQdpFtdcRspInvestorAccountField *pRspInvestorAccount, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    ///报单通知
    void OnRtnOrder(CQdpFtdcOrderField *pOrder);

    ///成交通知
    void OnRtnTrade(CQdpFtdcTradeField *pTrade);

// ---- 自定义函数 ---- //
public:
    bool loginFlag; // 登陆成功的标识

    void reqOrderInsert(
            TQdpFtdcInvestorIDType instrumentID,
            TQdpFtdcOffsetFlagType ocFlag,
            TQdpFtdcVolumeType volume,
            TQdpFtdcDirectionType direction); // 个性化报单录入，外部调用

    // void SubmitUserSystemInfo();

    void CusreqOrderInsert(
            TQdpFtdcInvestorIDType instrumentID,
            TQdpFtdcOffsetFlagType ocflag,
            TQdpFtdcVolumeType volume,
            TQdpFtdcDirectionType direction,
            TQdpFtdcPriceType limitprice,
            int orderid);// 个性化报单录入，外部调用
    void reqQueryInvestorPosition(TQdpFtdcInvestorIDType instrumentID); // 请求查询投资者持仓
    void reqQueryTradingAccount();
private:
    void reqUserLogin(); // 登录请求
    bool isErrorRspInfo(CQdpFtdcRspInfoField * pRspInfo); // 是否收到错误信息
};


class SimTradeSpi : public SimTraderSpi
{
// ---- ctp_api部分回调接口 ---- //
public:
    CQdpFtdcTraderApi *g_pTradeUserApi;                    // 交易指针
    char pcCTPTradeFrontAddr[28];                 // 交易前置地址  -- 国元次席
    TQdFtdcBrokerIDType pcBrokerID;                         // 模拟经纪商代码   中信
    TQdpFtdcInvestorIDType gInvestorID;                         // 投资者账户名
    TQdpFtdcUserIDType gUserID;                         // 投资者账户名
    TQdFtdcPasswordType pcQTPTradeInvesterPassword;                     // 投资者密码
    TQdFtdcAuthCodeType authcode;              //
    // 会话参数
    TQdFtdcFrontIDType trade_front_id;	//前置编号
    TQdFtdcSessionIDType session_id;	//会话编号
    TQdpFtdcCustomType order_ref;	//报单引用
    ServerCTAEngine * fp = nullptr;
    SimTradeSpi(ServerCTAEngine *p);

    ///当客户端与交易后台建立起通信连接时（还未登录前），该方法被调用。
    void OnFrontConnected();

    ///错误应答
    void OnRspError(CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    ///当客户端与交易后台通信连接断开时，该方法被调用。当发生这个情况后，API会自动重新连接，客户端可不做处理。
    void OnFrontDisconnected(int nReason);

    ///心跳超时警告。当长时间未收到报文时，该方法被调用。
    void OnHeartBeatWarning(int nTimeLapse);

    ///请求查询合约响应
    void OnRspQryInstrument(CQdpFtdcRspInstrumentField *pRspInstrument, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    ///报单录入请求响应
    void OnRspOrderInsert(CQdpFtdcInputOrderField *pInputOrder, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    ///报单操作请求响应
    void OnRspOrderAction(CQdpFtdcOrderActionField *pOrderAction, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    ///请求查询资金账户响应
	void OnRspQryInvestorAccount(CQdpFtdcRspInvestorAccountField *pRspInvestorAccount, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    ///报单通知
    void OnRtnOrder(CQdpFtdcOrderField *pOrder);

    ///成交通知
    void OnRtnTrade(CQdpFtdcTradeField *pTrade);

// ---- 自定义函数 ---- //
public:
    bool loginFlag; // 登陆成功的标识

    void reqOrderInsert(
            TQdpFtdcInvestorIDType instrumentID,
            TQdpFtdcOffsetFlagType ocFlag,
            TQdpFtdcVolumeType volume,
            TQdpFtdcDirectionType direction); // 个性化报单录入，外部调用

    // void SubmitUserSystemInfo();

    void CusreqOrderInsert(
            TQdpFtdcInvestorIDType instrumentID,
            TQdpFtdcOffsetFlagType ocflag,
            TQdpFtdcVolumeType volume,
            TQdpFtdcDirectionType direction,
            TQdpFtdcPriceType limitprice,
            int orderid);// 个性化报单录入，外部调用
    void reqQueryInvestorPosition(TQdpFtdcInvestorIDType instrumentID); // 请求查询投资者持仓
    void reqQueryTradingAccount();
private:
    void reqUserLogin(); // 登录请求
    bool isErrorRspInfo(CQdpFtdcRspInfoField * pRspInfo); // 是否收到错误信息
};

#endif
