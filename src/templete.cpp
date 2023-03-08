# include "templete.h"
# include "engine.h"
// -------------------------------------------
// BLOCK        内部回调函数相关
// -------------------------------------------

void Templete::onStart() {
    // 底层 onStart
    // std::cout << "onStart-Templete" << std::endl;
    // 策略 onStart
    this->pStrategy->onStart();
}


void Templete::onTick(const Tick& tick) {
    // std::cout<< "tick: " << tick.symbol<< " " <<tick.datetime.toStr() << std::endl;
    this->pStrategy->onTick(tick);
}

void Templete::onBar(const Bar& bar) {
    std::cout << "onBar" << std::endl;
}

void Templete::onOrderCancel(const Order& order) {
    std::cout << "order cancelled" << std::endl;
    this->pStrategy->onOrderCancel(order);
}

void Templete::onOrder(const Order& order) {
    std::cout << std::format("templete {:}, {:}, {:d}", order.symbol, order.offset, order.totalVolume) << std::endl;
    this->pStrategy->onOrder(order);
}

void Templete::onTrade(const Trade& trade) {
    this->pStrategy->onTrade(trade);
}

void Templete::onErr(const int& error) {
    this->pStrategy->onErr(error);
}



void Templete::update_ticks(Tick& tick) {}

void Templete::tick_interval(short interval){}

void Templete::order_target_fak(unsigned int target,
                            const char * symbol,
                            const char * exchange,
                            const char * investor,
                            bool direction) {

}

void Templete::subMarketdata(std::string symbol, std::string exchange) {
    this->pEngine->subMarketData(symbol, exchange);
}

bool Templete::bar_aligned() {
    return true;
}

void Templete::update_bars(Bar& bar) {}

void Templete::manage_position(bool init) {}

void Templete::load_data() {}

void Templete::create_file() {}

void Templete::write_data(Order& feedback) {}

# if !_SERVER_RUNTIME_MODE
void Templete::CompleteSubMarketData(const char * start, const char * end) {
    // this->pEngine->sendData();
}
# endif
