#include "SimTradeApi.h"

// Fake Exchange for simulate and backtesting.
class Exchange {
    using param_tuple = std::tuple<int, std::string, double, int>;
    using MD_map = std::unordered_map<std::string, Tick*>;
private:
    // 交易所自增 trade id
    int _TradeID;
    // 交易所自增 order id
    int _OrderID;
    // 交易所待处理报单信息
    std::queue<param_tuple> order_fak;
    // std::queue<> order_gfd
    // std::queue<> order_fok
    // std::queue<> cancel_order
    // 回测延迟成交信息
    char delay = 1;

    void _ProcessingOrder() {}
public:
    // 构造函数
    #if _SERVER_RUNTIME_MODE==0  // Backtesting
    Exchange(int delay=1) {
        this->delay = delay;
    }
    #else  // Simulation
    Exchange() {

    }
    #endif

    // 交易所主线程
    void _MainThread() {}

    // 数据接口： 获得最新行情
    void getLatestMData(Tick * tick) {}

    // 撤单接口：向交易所撤单
    void cancelOrder(int orderid) {}

    // 报单录入接口： 向交易所报单
    void addOrder(char ) {}

    //
    void getTrade() {}

    //
    void errorOrder() {}
};

class RealSimTraderApi: public SimTraderApi {
using param_tuple = std::tuple<int, std::string, double, int>;
private:
    const char * apiVersion = "1.0.0";
    SimTraderSpi *spi;
    Exchange *exchange;
    char frontAddr[32];

    void writeLog() {
        // thread
    }

public:
    const char * GetApiVersion() {return apiVersion;}
    void Init() {
        exchange = new Exchange();
    };

    int Join() {return 0;}

    void Release() {
        delete exchange;
        delete this;
    }

    const char * GetTradingDay() {return "";}

    void RegisterFront(char * frontAddr) {
        strcpy_s(this->frontAddr, frontAddr);
    }

    void RegisterSpi(SimTraderSpi* spi) {this->spi = spi;}

	///报单录入请求
	int ReqOrderInsert(CThostFtdcInputOrderField *pInputOrder, int nRequestID) {
        return 0;
    }

	///预埋单录入请求
	int ReqParkedOrderInsert(CThostFtdcParkedOrderField *pParkedOrder, int nRequestID) {
        return 0;
    }

	///预埋撤单录入请求
	int ReqParkedOrderAction(CThostFtdcParkedOrderActionField *pParkedOrderAction, int nRequestID){
        return 0;
    }

	///报单操作请求
	int ReqOrderAction(CThostFtdcInputOrderActionField *pInputOrderAction, int nRequestID) {
        return 0;
    }

	///查询最大报单数量请求
	int ReqQryMaxOrderVolume(CThostFtdcQryMaxOrderVolumeField *pQryMaxOrderVolume, int nRequestID) {
        return 0;
    }

	///投资者结算结果确认
	int ReqSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, int nRequestID) {
        return 0;
    }

	///请求删除预埋单
	int ReqRemoveParkedOrder(CThostFtdcRemoveParkedOrderField *pRemoveParkedOrder, int nRequestID) {
        return 0;
    }

	///请求删除预埋撤单
	int ReqRemoveParkedOrderAction(CThostFtdcRemoveParkedOrderActionField *pRemoveParkedOrderAction, int nRequestID) {
        return 0;
    }

    ///报价录入请求
	int ReqQuoteInsert(CThostFtdcInputQuoteField *pInputQuote, int nRequestID) {
        return 0;
    }

	///报价操作请求
	int ReqQuoteAction(CThostFtdcInputQuoteActionField *pInputQuoteAction, int nRequestID) {
        return 0;
    }

	///批量报单操作请求
	int ReqBatchOrderAction(CThostFtdcInputBatchOrderActionField *pInputBatchOrderAction, int nRequestID) {
        return 0;
    }

	///请求查询报单
	int ReqQryOrder(CThostFtdcQryOrderField *pQryOrder, int nRequestID) {
        return 0;
    }

	///请求查询成交
	int ReqQryTrade(CThostFtdcQryTradeField *pQryTrade, int nRequestID) {
        return 0;
    }

	///请求查询投资者持仓
	int ReqQryInvestorPosition(CThostFtdcQryInvestorPositionField *pQryInvestorPosition, int nRequestID) {
        return 0;
    }

	///请求查询预埋单
	int ReqQryParkedOrder(CThostFtdcQryParkedOrderField *pQryParkedOrder, int nRequestID) {
        return 0;
    }

	///请求查询预埋撤单
	int ReqQryParkedOrderAction(CThostFtdcQryParkedOrderActionField *pQryParkedOrderAction, int nRequestID) {
        return 0;
    }

};


SimTraderApi* SimTraderApi::CreateSimTraderApi(const char *) {
    return new RealSimTraderApi;
}


