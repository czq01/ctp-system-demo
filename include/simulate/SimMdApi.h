#ifndef __BACKTEST_API_
#define __BACKTEST_API_

#if _MSC_VER > 1000
#pragma once
#endif

#include "ThostFtdcUserApiStruct.h"
#include "ThostFtdcUserApiDataType.h"
#include "base.h"

#if defined(ISLIB) && defined(WIN32)
#ifdef LIB_MD_API_EXPORT
#define BACKTEST_MD_API_EXPORT __declspec(dllexport)
#else
#define BACKTEST_MD_API_EXPORT __declspec(dllimport)
#endif
#else
#define BACKTEST_MD_API_EXPORT
#endif

class SimMdSpi;
class BACKTEST_MD_API_EXPORT SimMdApi {
public:
	///@param pszFlowPath 存贮订阅信息文件的目录
	static SimMdApi *CreateSimMdApi(const char *pszFlowPath = "",
	const bool bIsUsingUdp=false, const bool bIsMulticast=false);

	virtual const char *GetApiVersion() = 0;

	// delete API
	virtual void Release() = 0;

	// Initialize API
	virtual void Init() = 0;

	// waiting for thread exit
	///@return exit code
	virtual int Join()=0;

	virtual const char *GetTradingDay() = 0;

	///@remark format: "protocol://ipaddress:port". eg. "tcp://127.0.0.1:17001"。
	virtual void RegisterFront(char *pszFrontAddress) = 0;

	virtual void RegisterSpi(SimMdSpi *pSpi) = 0;

	virtual int SubscribeMarketData(char *ppInstrumentID[], int nCount, int sid) = 0;
	// TODO 一把子订阅 （Issue #13）
	virtual int CompleteSubMarketData(int sid, const char * start, const char * end) =0;
protected:
	~SimMdApi(){};
};

class SimMdSpi {
public:
	///当客户端与交易后台建立起通信连接时（还未登录前），该方法被调用。
	virtual void OnFrontConnected(){};

	///当客户端与交易后台通信连接断开时，该方法被调用。当发生这个情况后，API会自动重新连接，客户端可不做处理。
	///@param nReason 错误原因
	///        0x1001 网络读失败
	///        0x1002 网络写失败
	///        0x2001 接收心跳超时
	///        0x2002 发送心跳失败
	///        0x2003 收到错误报文
	virtual void OnFrontDisconnected(int nReason){};

	///错误应答
	virtual void OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///订阅行情应答
	virtual void OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///取消订阅行情应答
	virtual void OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///深度行情通知
	virtual void OnRtnDepthMarketData(Tick *pDepthMarketData, const int& sid) {};

};

#endif