// 模板样例
//

# include "templete.h"

class ToMySQL {
    MYSQL * mysql = nullptr;
    std::map<std::string, char *> mSQLCommandLine;
    std::map<std::string, char> mSQLAggregateCount;
    std::map<std::string, DateTime> mLastSymbolDatetime;
    int length = 16383;
    int recon = 0;
public:
    ToMySQL(){run();}

    void get_data(const Tick & tick){
        // hiden implementations
    }

    void registration(const char * symbol){
        // hiden implementations
    }

    void run() {
        // hiden implementations
    }

    ~ToMySQL(){
        // hiden implementations
    }
};

class Strategy_example: public Templete {
    public:
        // For Data storage
        ToMySQL * sql = nullptr;
        Strategy_example() {
            std::function<void(Bar&)> onBar = std::bind(&Strategy_example::onBar,this,std::placeholders::_1);
            bms = BarManager(onBar);
            sql = new ToMySQL;
        };

        ~Strategy_example() {
            delete sql;
        }

        void onTick(const Tick& tick){
            std::cout<< "tick: " << tick.symbol<< " " <<tick.datetime << std::endl;
            sql->get_data(tick);
        };

        void onOrder(const Order& order) {
            const DateTime& now = order.orderTime;
            std::cout << std::format(
                "order {:}, {:d}, {:d}, {:d}, {:}",
                order.symbol, order.offset,
                order.totalVolume, order.direction,
                order.orderTime.toStr()
            ) << std::endl;
        }

        void onTrade(const Trade& trade) {
            std::cout << std::format("trade {:}: offset={:d}, volume={:d}", trade.symbol, trade.offset, trade.volume) << std::endl;
        }

        void onBar(const Bar& bar) {

        }

        void onStart() {
            // 需订阅的合约
            sql->registration("Ag(T+D)");
            this->subMarketdata("Ag(T+D)", "SGE");
            this->subMarketdata("c2205", "DCE");
            this->subMarketdata("au2212P432", "SHFE");
        }
};
