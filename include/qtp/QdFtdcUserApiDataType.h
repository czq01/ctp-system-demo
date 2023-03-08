﻿/////////////////////////////////////////////////////////////////////////
///@system QuantDo Platform
///@company QuantDo
///@file QdFtdcUserApiDataType.h
///@brief 定义了客户端接口使用的业务数据类型
///@history 
///
/////////////////////////////////////////////////////////////////////////

#ifndef QD_FTDCDATATYPE_H
#define QD_FTDCDATATYPE_H

enum QD_TE_RESUME_TYPE
{
	QD_TERT_RESTART = 0,
	QD_TERT_RESUME,
	QD_TERT_QUICK
};

/////////////////////////////////////////////////////////////////////////
///定义交易通道类型类别
/////////////////////////////////////////////////////////////////////////
//连接中金所
#define QD_EI_CFFEX "CFFEX"
//连接上期所
#define QD_EI_SHFE "SHFE"
//连接大商所
#define QD_EI_DCE "DCE"
//连接郑商所
#define QD_EI_CZCE "CZCE"
//连接上证所
#define QD_EI_SSE "SSE"
//连接深交所
#define QD_EI_SZSE "SZSE"
//连接黄金交易所
#define QD_EI_SGE "SGE"
//连接芝加哥商品期货交易所
#define QD_EI_CME "CME"
//连接伦敦金属交易所
#define QD_EI_LME "LME"
//连接国泰君安的通道
#define QD_EI_GTJA "GTJA"
//连接上海国际能源中心的通道
#define QD_EI_INE "INE"
//连接无锡不锈钢
#define QD_EI_BXG "BXG"

//连接新加坡交易所
#define QD_EI_SGX "SGX"

//连接新加坡APEX交易所
#define QD_EI_APEX "APEX"

//连接纽约商业交易所
#define QD_EI_NYMEX "NYMEX"
//连接香港交易所
#define QD_EI_HKEX "HKEX"
//连接马来西亚交易所
#define QD_EI_BMD "BMD"
//连接芝加哥期货交易所
#define QD_EI_CBOT "CBOT"
//连接纽约期货交易所
#define QD_EI_NYBOT "NYBOT"
//连接东京商品交易所 
#define QD_EI_TOCOM "TOCOM"
//连接韩国交易所
#define QD_EI_KRX "KRX"
//连接伦敦国际金融期货交易所
#define QD_EI_LIFFE "LIFFE"


const int QD_TSS_DIALOG = 1;		//对话流
const int QD_TSS_PRIVATE = 2;		//客户私有流
const int QD_TSS_PUBLIC = 3;		//公共流
const int QD_TSS_QUERY = 4;		//查询
const int QD_TSS_USER = 5;		//用户私有流
const int QD_TSS_MARKET = 6;		//MBL行情流

/////////////////////////////////////////////////////////////////////////
///TFtdcPriceType是一个价格类型
/////////////////////////////////////////////////////////////////////////
typedef double TQdFtdcPriceType;

/////////////////////////////////////////////////////////////////////////
///TFtdcMoneyType是一个资金类型
/////////////////////////////////////////////////////////////////////////
typedef double TQdFtdcMoneyType;

/////////////////////////////////////////////////////////////////////////
///TFtdcLargeVolumeType是一个大额数量类型
/////////////////////////////////////////////////////////////////////////
typedef double TQdFtdcLargeVolumeType;

/////////////////////////////////////////////////////////////////////////
///TFtdcRatioType是一个比率类型
/////////////////////////////////////////////////////////////////////////
typedef double TQdFtdcRatioType;

/////////////////////////////////////////////////////////////////////////
///TFtdcNumberType是一个编号类型
/////////////////////////////////////////////////////////////////////////
typedef int TQdFtdcNumberType;

/////////////////////////////////////////////////////////////////////////
///TFtdcErrorIDType是一个错误代码类型
/////////////////////////////////////////////////////////////////////////
typedef int TQdFtdcErrorIDType;

/////////////////////////////////////////////////////////////////////////
///TFtdcDataCenterIDType是一个数据中心代码类型
/////////////////////////////////////////////////////////////////////////
typedef int TQdFtdcDataCenterIDType;

/////////////////////////////////////////////////////////////////////////
///TFtdcSessionIDType是一个会话编号类型
/////////////////////////////////////////////////////////////////////////
typedef int TQdFtdcSessionIDType;

/////////////////////////////////////////////////////////////////////////
///TFtdcFrontIDType是一个前置编号类型
/////////////////////////////////////////////////////////////////////////
typedef int TQdFtdcFrontIDType;

/////////////////////////////////////////////////////////////////////////
///TFtdcSequenceNoType是一个序列号类型
/////////////////////////////////////////////////////////////////////////
typedef int TQdFtdcSequenceNoType;

/////////////////////////////////////////////////////////////////////////
///TFtdcSequenceSeriesType是一个序列系列号类型
/////////////////////////////////////////////////////////////////////////
typedef int TQdFtdcSequenceSeriesType;

/////////////////////////////////////////////////////////////////////////
///TFtdcMillisecType是一个最后修改毫秒类型
/////////////////////////////////////////////////////////////////////////
typedef int TQdFtdcMillisecType;

/////////////////////////////////////////////////////////////////////////
///TFtdcVolumeType是一个数量类型
/////////////////////////////////////////////////////////////////////////
typedef int TQdFtdcVolumeType;

/////////////////////////////////////////////////////////////////////////
///TFtdcTopicIDType是一个主题代码类型
/////////////////////////////////////////////////////////////////////////
typedef int TQdFtdcTopicIDType;

/////////////////////////////////////////////////////////////////////////
///TFtdcSettlementIDType是一个结算编号类型
/////////////////////////////////////////////////////////////////////////
typedef int TQdFtdcSettlementIDType;

/////////////////////////////////////////////////////////////////////////
///TFtdcPacketNoType是一个结算编号类型
/////////////////////////////////////////////////////////////////////////
typedef int TQdFtdcPacketNoType;

/////////////////////////////////////////////////////////////////////////
///TFtdcBoolType是一个布尔型类型
/////////////////////////////////////////////////////////////////////////
typedef int TQdFtdcBoolType;

/////////////////////////////////////////////////////////////////////////
///TFtdcUserIDType是一个用户代码类型
/////////////////////////////////////////////////////////////////////////
typedef char TQdFtdcUserIDType[19];

/////////////////////////////////////////////////////////////////////////
///TFtdcQdpUserIDType是一个用户代码类型
/////////////////////////////////////////////////////////////////////////
typedef char TQdFtdcQdpUserIDType[16];

/////////////////////////////////////////////////////////////////////////
///TFtdcBrokerIDType是一个经纪公司编号类型
/////////////////////////////////////////////////////////////////////////
typedef char TQdFtdcBrokerIDType[11];

/////////////////////////////////////////////////////////////////////////
///TFtdcPasswordType是一个密码类型
/////////////////////////////////////////////////////////////////////////
typedef char TQdFtdcPasswordType[41];

/////////////////////////////////////////////////////////////////////////
///TFtdcProductInfoType是一个产品信息类型
/////////////////////////////////////////////////////////////////////////
typedef char TQdFtdcProductInfoType[51];

/////////////////////////////////////////////////////////////////////////
///TFtdcQdpProductInfoType是一个产品信息类型
/////////////////////////////////////////////////////////////////////////
typedef char TQdFtdcQdpProductInfoType[41];

/////////////////////////////////////////////////////////////////////////
///TFtdcProtocolInfoType是一个协议信息类型
/////////////////////////////////////////////////////////////////////////
typedef char TQdFtdcProtocolInfoType[41];

/////////////////////////////////////////////////////////////////////////
///TFtdcIPAddressType是一个IP地址类型
/////////////////////////////////////////////////////////////////////////
typedef char TQdFtdcIPAddressType[21];

/////////////////////////////////////////////////////////////////////////
///TFtdcMacAddressType是一个Mac地址类型
/////////////////////////////////////////////////////////////////////////
typedef char TQdFtdcMacAddressType[21];

/////////////////////////////////////////////////////////////////////////
///TFtdcDateType是一个日期类型
/////////////////////////////////////////////////////////////////////////
typedef char TQdFtdcDateType[9];

/////////////////////////////////////////////////////////////////////////
///TFtdcTimeType是一个时间类型
/////////////////////////////////////////////////////////////////////////
typedef char TQdFtdcTimeType[9];

/////////////////////////////////////////////////////////////////////////
///TFtdcUserOrderLocalIDType是一个用户本地报单号类型
/////////////////////////////////////////////////////////////////////////
typedef char TQdFtdcUserOrderLocalIDType[23];

/////////////////////////////////////////////////////////////////////////
///TFtdcTradingSystemNameType是一个交易系统名称类型
/////////////////////////////////////////////////////////////////////////
typedef char TQdFtdcTradingSystemNameType[61];

/////////////////////////////////////////////////////////////////////////
///TFtdcLoginInfoType是一个登录信息类型
/////////////////////////////////////////////////////////////////////////
typedef char TQdFtdcLoginInfoType[257];

/////////////////////////////////////////////////////////////////////////
///TFtdcTradingDayType是一个交易日类型
/////////////////////////////////////////////////////////////////////////
typedef char TQdFtdcTradingDayType[9];

/////////////////////////////////////////////////////////////////////////
///TFtdcInstrumentIDType是一个合约编号类型
/////////////////////////////////////////////////////////////////////////
typedef char TQdFtdcInstrumentIDType[31];

/////////////////////////////////////////////////////////////////////////
///TFtdcExchangeIDType是一个交易(所)通道类型
/////////////////////////////////////////////////////////////////////////
typedef char TQdFtdcExchangeIDType[11];

/////////////////////////////////////////////////////////////////////////
///TFtdcSettlementGroupIDType是一个结算组代码类型
/////////////////////////////////////////////////////////////////////////
typedef char TQdFtdcSettlementGroupIDType[9];

/////////////////////////////////////////////////////////////////////////
///TFtdcErrorMsgType是一个错误信息类型
/////////////////////////////////////////////////////////////////////////
typedef char TQdFtdcErrorMsgType[129];

/////////////////////////////////////////////////////////////////////////
///TFtdcQdpErrorMsgType是一个错误信息类型
/////////////////////////////////////////////////////////////////////////
typedef char TQdFtdcQdpErrorMsgType[81];

/////////////////////////////////////////////////////////////////////////
///TFtdcAuthCodeType是一个授权编码类型
/////////////////////////////////////////////////////////////////////////
typedef char TQdFtdcAuthCodeType[129];

/////////////////////////////////////////////////////////////////////////
///TFtdcInstrumentStatusType是一个合约交易状态类型
/////////////////////////////////////////////////////////////////////////
///开盘前
#define QD_FTDC_IS_BeforeTrading '0'
///非交易
#define QD_FTDC_IS_NoTrading '1'
///连续交易
#define QD_FTDC_IS_Continous '2'
///集合竞价报单
#define QD_FTDC_IS_AuctionOrdering '3'
///集合竞价价格平衡
#define QD_FTDC_IS_AuctionBalance '4'
///集合竞价撮合
#define QD_FTDC_IS_AuctionMatch '5'
///收盘
#define QD_FTDC_IS_Closed '6'
///开盘集合竞价
#define QD_FTDC_IS_OpenAuction '7'
///收盘集合竞价
#define QD_FTDC_IS_CloseAuction '8'
///临时停牌
#define QD_FTDC_IS_TemporaryHalt '9'
///停牌
#define QD_FTDC_IS_AlldayHalt 'a'
///盘后交易
#define QD_FTDC_IS_AfterTradingDeal 'b'
///波动性中断
#define QD_FTDC_IS_WaveInterrupt 'c'
///休市
#define QD_FTDC_IS_BreakTime 'd'
///未上市
#define QD_FTDC_IS_NoTraded 'e'

typedef char TQdFtdcInstrumentStatusType;

/////////////////////////////////////////////////////////////////////////
///TFtdcDirectionType是一个买卖方向类型
/////////////////////////////////////////////////////////////////////////
///买
#define QD_FTDC_D_Buy '0'
///卖
#define QD_FTDC_D_Sell '1'

typedef char TQdFtdcDirectionType;

/////////////////////////////////////////////////////////////////////////
///TFtdcManalSetVolType是一个用户设置波动率类型
/////////////////////////////////////////////////////////////////////////
///YES
#define QD_FTDC_IS_SET '1'
///NOT
#define QD_FTDC_IS_NOTSET '0'

typedef char TQdFtdcManalSetVolType;

#endif
