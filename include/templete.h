#ifndef __STRATEGY_TEMPLETE
#define __STRATEGY_TEMPLETE

#include "base.h"
#include "json.h"

class CTAEngine;

class Templete {
protected:
    /* data */
    //仓位信息
    pos_list pos;       // 总投机方向
    pos_list tpos;      // 今持仓位
    pos_list ypos;      // 昨持仓位
    order_list orders;  // 在途单表
    std::string symbolList;
    BarManager bms;     // 合成Bar

protected:
    // 内建函数

    /* 下单函数 */

    // 目标报单
    // target: 目标;  investor: 投资者账号; exchange: 交易所;  direction: 0多头/1空头
    void order_target_fak(unsigned int target, const char* symbol, const char* exchange,
                      const char* investor, bool direction);
    int sendOrderGFD(const char * symbol, unsigned int volume);
    int sendOrderFAK(const char * symbol, unsigned int volume);
    int sendOrderFOK(const char * symbol, unsigned int volume);
    // 直接报单
    void update_bars(Bar& bar);
    void tick_interval(short interval);
    // 策略入口
    void update_ticks(Tick& tick);
    bool bar_aligned();
    void subMarketOptions(char * underlying,int upper, int lower, int interval);

    #if !_SERVER_RUNTIME_MODE
    // 完成订阅请求
    void CompleteSubMarketData(const char * start, const char * end);
    #endif

public:
    CTAEngine *pEngine;
    Templete * pStrategy = nullptr;
    void manage_position(bool init);
    void load_data();
    void create_file();
    void write_data(Order& feedback);
    void subMarketdata(std::string symbol, std::string exchange);

    // 可重写方法
    virtual void onBar(const Bar& bar);
    virtual void onOrderCancel(const Order& order);

    // 以下函数会先于策略对应函数执行
    virtual void onTick(const Tick& tick);
    virtual void onStart();
    virtual void onOrder(const Order& order);
    virtual void onTrade(const Trade& trade);
    virtual void onErr(const int& error);
};




// engine -> templete
// strategy -> templete

#endif

