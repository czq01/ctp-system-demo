#ifndef _BASE_H_
#define _BASE_H_

/**
 * @file base.h
 * @authors
 * @brief 这是一个基类文件，用于存放数据结构及常量定义。
 * @attention 基类定义按所给结构封装，模板类定义实现需置于头文件中。
 * @version 0.1
 * @date 2022-01-23
 *
 * @copyright Copyright (c) 2022
 *
 */

// 防止Winsock2 在include Windows.h时引入 Winsock.h
// #define _WINSOCKAPI_
#include "ThostFtdcUserApiStruct.h"
#include "datetime.h"
#include "mysql.h"
#include <chrono>
#include <functional>
#include <list>
#include <map>
#include <queue>
#include <thread>
#include <tuple>
#include <vector>

#if _HAS_CXX20
#include <numbers>
#include <semaphore>
#endif

// ---------------------------------------------------
// BLOCK     常量定义   Constant Definition
// ---------------------------------------------------
// 此处定义所有交易中用到的常量。所有枚举常量均使用int类型替代。
// 所有整形常量均使用数字类型进行宏定义替换。
// 其它常量使用 const 进行定义
//

// CTA引擎中涉及到的交易方向类型
constexpr inline char CTAORDER_BUY[] = "买开"; // buy 买开
constexpr inline char CTAORDER_SELL[] = "卖平"; // sell 卖平
constexpr inline char CTAORDER_SELL_TODAY[] = "卖平今"; // sell_t 卖平今
constexpr inline char CTAORDER_SHORT[] = "卖开"; // short 卖开
constexpr inline char CTAORDER_COVER[] = "买平"; // cover 买平
constexpr inline char CTAORDER_COVER_TODAY[] = "买平今"; // cover_t 买平今

// 多空方向类型
constexpr inline bool SYMBOL_DIRECTION_LONG = 0; // 头寸方向-多
constexpr inline bool SYMBOL_DIRECTION_SHORT = 1; // 头寸方向-空
constexpr inline bool TRADE_DIRECTION_LONG = 0; // 交易方向-多
constexpr inline bool TRADE_DIRECTION_SHORT = 1; // 交易方向-空
constexpr inline bool DIRECTION_LONG = 0; //     方向-多
constexpr inline bool DIRECTION_SHORT = 1; //     方向-空

// 报单类型
constexpr inline char ORDER_LIMIT_GFD = '0'; // 限价GFD
constexpr inline char ORDER_LIMIT_FAK = '1'; // 限价FAK
constexpr inline char ORDER_LIMIT_FOK = '2'; // 限价FOK
constexpr inline char ORDER_ANY_PRICE = '3'; // 市价 （上期所不适用 - 涨跌停限价）

// 本地停止单状态
constexpr inline char STOPORDER_WAITING = '0'; // awaiting 等待中
constexpr inline char STOPORDER_CANCELLED = '4'; // cancelled 报单被撤
constexpr inline char STOPORDER_TRIGGERED = '3'; // submitted 已提交

// 报单状态
constexpr inline char ORDER_SUBMITTED = '0'; // 报单已提交
constexpr inline char ORDER_ACCEPTTED = '1'; // 报单已接受
constexpr inline char ORDER_WRONG = '2'; // 本地核查错单
constexpr inline char ORDER_TRADEDED = '3'; // 报单已成交
constexpr inline char ORDER_REFUSED = '4'; // 报单被拒

// 其他常量
#if _HAS_CXX20
using std::numbers::e;
using std::numbers::pi;
#define PI pi
#elif _HAS_CXX17
constexpr double pi = 3.1415926535897932;
constexpr double e_ = 2.71828;
#define PI pi
#else
#define PI 3.1415926
#define E_ 2.71828
#endif
// constexpr int MAX_SID =64; 暂时放到了外面。
const Time TIME_DAY_OPEN(8, 50, 0, 0); // 日盘开盘
const Time TIME_DAY_CLOSE_QTP(15, 30, 0, 0); // QTP日盘收盘
const Time TIME_DAY_CLOSE_CTP(15, 0, 0, 0); // QTP日盘收盘
const Time TIME_NIGHT_OPEN(20, 50, 0, 0); // 夜盘开盘
const Time TIME_NIGHT_CLOSE(2, 30, 0, 0); // 夜盘收盘

// -----------------------------------------------------
// BLOCK  类型定义及声明  Type Definition & Declaration
// -----------------------------------------------------
// 此处使用 typedef 将常用的模板类型予以别名。
// 部分结构体亦在此处进行预声明。
//

class Position;

// 数字字典
typedef std::unordered_map<std::string, double> num_dict;
// string 字典
typedef std::unordered_map<std::string, std::string> dict;

// ---------------------------------------------------
// BLOCK    功能函数声明  Function Declaration
// ---------------------------------------------------
// 此处声明全局功能函数及全局模板函数。
// 并同时对模板函数进行函数定义。
//

// inline unsigned long GetCycleCount() {
//     __asm   RDTSC
// }

int sqlInit(MYSQL*& mysql, const char* host, const char* user, const char* passwd, const char* db, int port);

// 正态分布概率密度函数
double norm_cdf(double);

double minimize(std::function<float(float)>, double, const char*);

double root(std::function<float(float)>, double);

// ---------------------------------------------------
// BLOCK   结构体定义  Structure Object Definition
// ---------------------------------------------------
/** 此处定义所有的结构体及基础类
 *  class baseBarData  修改了原vtObject.py中的VtBarData结构
 *  class Base       原vtObject.py中的数据结构
 *  class Tick       原vtObject.py中的数据结构
 *  class Order      原vtObject.py中的数据结构
 *  class Trade      原vtObject.py中的数据结构
 */

class Base {
public:
    Base();
    Base(const char* symbol, const char* exchange);
    char symbol[16]; // 完整合约代码
    const char* contractType; // 合约标识符
    const char* contractDate; // 到期日
    char exchange[6]; // 交易所
    friend std::ostream& operator<<(std::ostream& os, const Base&);
};

class Bar : public Base {
public:
    Bar();
    // 成交数据
    double openPrice; // 今日开盘价
    double highPrice; // 今日最高价
    double lowPrice; // 今日最低价
    double closePrice; // 今日盘价
    DateTime datetime; // 时间
    int volume; // 成交量
    friend std::ostream& operator<<(std::ostream& os, const Bar&);
};

class FutureBar : public Bar {
public:
    FutureBar();
    double openInterest; // 持仓量
};

class Tick : public Base {
public:
    Tick();
    Tick(const char* symbol, const char* exchange, double lastP, int lastVol,
         DateTime dt, double askP1, int askVol1, double bidP1, int bidVol1);
    Tick(const CThostFtdcDepthMarketDataField *);
    // 成交数据
    double lastPrice; // 最新成交价
    int lastVolume; // 最新成交量
    DateTime datetime; // 时间

    // 常规行情
    double openPrice; // 今日开盘价
    double highPrice; // 今日最高价
    double lowPrice; // 今日最低价
    double preClosePrice; // 昨收盘价
    double upperLimit; // 涨停价
    double lowerLimit; // 跌停价
    double turnover; // 成交量

    // 五档行情
    double bidPrice1; // 买一
    double bidPrice2; // 买二
    double bidPrice3; // 买三
    double bidPrice4; // 买四
    double bidPrice5; // 买五

    double askPrice1; // 卖一
    double askPrice2; // 卖二
    double askPrice3; // 卖三
    double askPrice4; // 卖四
    double askPrice5; // 卖五

    int bidVolume1; // 买一量
    int bidVolume2; // 买二量
    int bidVolume3; // 买三量
    int bidVolume4; // 买四量
    int bidVolume5; // 买五量

    int askVolume1; // 卖一量
    int askVolume2; // 卖二量
    int askVolume3; // 卖三量
    int askVolume4; // 卖四量
    int askVolume5; // 卖五量
    friend std::ostream& operator<<(std::ostream& os, const Tick&);
};

class FutureTick : public Tick {
public:
    FutureTick();
    FutureTick(char* symbol, char* exchange, double lastP, int lastV, DateTime dt,
               double askP1, int askV1, double bidP1, int bidV1);
    FutureTick(const CThostFtdcDepthMarketDataField *);
    char* exchangeInstID;
    double preOpenInterest; // 昨持仓
    double preSettlementPrice; // 昨结算价
    double openInterest; // 今持仓
};

class Order : public Base {
public:
    Order();
    Order(int, double, const char*, const char*);
    Order(const CThostFtdcOrderField&);
    char symbol[10]; // 合约代码
    char vtSymbol[10]; // 交易所代码
    char orderID[6]; // 订单编号
    char vtOrderID[6]; // 订单编号
    // 报单相关
    char direction; // 报单方向
    char offset; // 报单开平仓
    double price; // 报单价格
    char priceType; // 报单价格
    int totalVolume; // 报单总数量
    int tradedVolume; // 报单成交数量
    char status; // 报单状态
    char orderTime[24]; // 发单时间
    // CTP/LTS相关
    int frontID; // 前置机编号
    int sessionID; // 连接编号
    friend std::ostream& operator<<(std::ostream& os, const Order&);
};

class Trade : public Base {
public:
    Trade(const CThostFtdcTradeField&);
    char symbol[10]; // 合约代码
    char vtSymbol[10]; // 交易所代码
    char tradeID[6]; // 成交编号
    char vtTradeID[6]; // 成交编号
    char orderID[6]; // 订单编号
    char vtOrderID[6]; // 订单编号

    // 成交相关
    char direction; // 成交方向
    char offset; // 成交开平仓
    double price; // 成交价格
    int volume; // 成交数量
    char tradeTime[24]; // 成交时间
    double commission; // 手续费
    friend std::ostream& operator<<(std::ostream& os, const Trade& trade);
};


// ---------------------------------------------------
// BLOCK  功能类定义  Functional Class Definition
// ---------------------------------------------------
/** 此处定义所有的功能类
 *  @main: 仓位
 *  class BarMagagers    Bar管理: 该类为TickManager所需要的数据结构
 *  class TickManagers   Tick管理: 支持任意间隔(时间或Tick)K线合成及onBar定时调用
 *  class BaseStructure 仓位管理基类
 *  class Pos           仓位管理
 *  @submain: 次要:
 *  class BoundsData    上下轨数据模块
 *  class Bounds        压力测试模块
 *  @others: 其他:
 *  (暂无)
 */


class Position {
    // _pos单向头寸持仓: _Pos[SymbolDirection]
    using _Pos = unsigned short[2];
    // 仓位类型
    typedef std::unordered_map<std::string, _Pos> PosDict;
public:
    // Register User, can be use to reset position.
    void userRegister(const std::string& symbol);
    // Order Change
    void makeOrder(const std::string& symbol, bool tradeDirection, bool offset, int volume);
    // Order Change
    void cancelOrder(const std::string& symbol, bool tradeDirection, bool offset, int volume);
    // Trade
    void makeTrade(const std::string& symbol, bool tradeDirection, bool offset, int volume);
    // 获取实际持仓数据
    const _Pos& getPos(const std::string& symbol);
    // TODO 函数体定义
    void makeOrder(const Order& order, bool isCancel);
    void makeTrade(const Trade& trade);
};


class TickManager {
    // TODO: TickManager对象的声明及定义
};

class ArrayManager {
public:
    ArrayManager(int maxsize, int size);
    bool updateBar(Bar bar);
    int size; // 缓存大小
    int maxsize;
    int count; // 缓存计数
    bool inited;
    std::queue<double> openArray;
    std::queue<double> highArray;
    std::queue<double> lowArray;
    std::queue<double> closeArray;
    std::queue<int> volumeArray;
};

class Option {
    /**
     * @brief 期权实例
     *
     * @param cp : 'c'->call, 'p'->put.
     * @param price : 期权价格
     * @param k : Strike price
     * @param time : 到期时间: 日？
     * @param r : 无风险利率 interest.
     * @param sigma  σ 隐含波动率
     * @param marketp
     * @param dv : 股息率？
     */
public:
    // ---------类成员变量----------
    char cp; // call_put (cp)
    char cp_sign; // call_put (+-)
    float price; // 价格 price
    int k; // 行权价 Strike price
    double t; // 到期时间
    double sigma; // 隐含波动率
    double r; // 无风险利率
    float dv; // 股息率

    // BAW中间公式变量
    double marketp, M, N, K_t, q, star, a;

    // ---------类成员函数----------
    Option(char cp, float price, int k, double time,
        double r, double sigma, double marketp, float dv = 0);
    // BS定价模型相关
    double d_1(), d_2(), d_1_1(), d_2_1();
    double BS_price();
    double BS_delta(), BS_Gamma(), BS_Vega(), BS_Theta();
    double BS_Rho(), BS_RhoQ(), BS_Vanna(), BS_IV();
    double BS_IV_newton(), BS_IV_func(double sigma);
    // TODO minimize和root函数暂时没法实现
    double BS_IV_optimize(), BS_IV_root();
    // 二叉树定价模型  美式期权
    double* CRR_m();
    double CRR_m_price(), CRR_m_Delta();
    double CRR_m_Gamma(), CRR_m_Vega();
    double CRR_m_Theta(), CRR_m_Rho();
    // 蒙卡特最小二乘 美式期权
    float Lsm();
    // BAW定价模型 美式期权
    double Baw_func(float price), d_1_sx(double price);
    void Baw_simulate(); // 定价模型方程求解
    void A();
    double Baw_price(), Baw_Delta(), Baw_Gamma(), Baw_Vega();
    double Baw_Theta(), Baw_Rho(), Baw_IV();
    // 三叉树定价
    double Back_tree_m(); // 美式期权
    double Back_tree(); // 欧式期权
};

class Montecarlo {
    Montecarlo(char cp, int N_samples, int D_stock, float t,
        float price0, float r, float* sigma_vector,
        float** correl_matrix,
        float* m_vector, int k);
    float Analog();
};

#endif