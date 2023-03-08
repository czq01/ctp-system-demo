#include "SimMdApi.h"

class SubMarketThreadPool {
    // 参数对类型
    using param_pair = std::pair<std::string, std::string>;
    // 二元信号量类型
    using bool_sig = std::binary_semaphore;
private:
    // 线程数(1<<n)
    int iThreadNum=4;
    // 数据线程池
    std::jthread ** threadpool = nullptr;
    // 队列访问锁
    bool_sig pBlockSig;
    // 线程终止信号量
    bool bArrTermSig = false;
    // 任务顺序锁(a锁b，b缩c，c锁a)
    bool_sig ** bArrOrderSig = nullptr;
    // 队列空闲状态锁
    bool_sig pTaskSig;
    // 子线程运行状态 (空闲为true)
    bool * bArrThreadStatus = nullptr;
    // 主线程运行状态 (空闲为true)
    bool MainThreadStatus = false;

    // 回测标的
    std::vector<std::string> *arrSubscribe;
    // 子线程任务队列
    std::queue<param_pair> qSubTasks;
    // 推送Queue
    std::queue<Tick*> qTicks;
    // 顺序计数
    unsigned int count = 0;
    // 各线程单次查询 预取数据长度
    const Time INTERVAL = Time("04:00:00.000");
    // MySQL连接参数
    MYSQL ** arrMySQL;


    // 启动子线程
    void __Start_SubThread() {
        // hiden implementations
    }

    // 主线程函数 - 分解任务
    void __MainThread(const char * start, const char * end) {
        // Hiden Part
    }

    // 子任务线程函数 - 根据任务获取数据
    void __DataThread(int flag) {
        // Hiden Part
    }

public:
    // 不允许无参构造
    explicit SubMarketThreadPool() = delete;

    // 参数构造
    explicit SubMarketThreadPool(std::vector<std::string> *qSubscribe,int ThreadNum=4):
        iThreadNum(ThreadNum), pBlockSig(0), bArrThreadStatus(new bool[ThreadNum]{0}),
        threadpool(new std::jthread *[ThreadNum]), pTaskSig(0),
        arrSubscribe(qSubscribe) {
            // hiden implementations
    }

    // 启动运行
    void start(const char * start, const char * end) {
        std::jthread main(&SubMarketThreadPool::__MainThread, this, start, end);
        main.detach();
    }

    // 获取结果（返回队列引用）
    std::queue<Tick*>& GetData() {return this->qTicks;}

    // request终止线程
    void reqTerminate() {
        // hiden implementations
    }

    // 线程池状态
    // (0:空闲中 1:运行中)
    bool getStatus() {
        // hiden implementations
    }

    // 析构函数
    ~SubMarketThreadPool() {
        // Hiden
    }

};


// 实现类Api
class RealSimApi: public SimMdApi {
    // 参数类型
    using param_pair = std::pair<std::string, std::string>;
    // sid-task映射类型
    using task_map = std::map<int, std::vector<std::string>*>;
    // 二元信号量类型
    using bool_sig = std::binary_semaphore;
private:
    // Api版本信息
    const char * apiVersion = "1.0.0";
    // Spi回调接口
    SimMdSpi * spi = nullptr;
    // 前置地址（暂时弃用）
    char frontAddr[29];
    // SID任务线程
    std::map<int,SubMarketThreadPool *> threadpool;
    // SID任务状态 (空闲为true)
    std::map<int, bool> poolStatus;
    // 主线程
    std::jthread * mainThread = nullptr;
    // 主线程终止信号
    bool pTermiSig = false;
    // map: sid-任务
    task_map mSidTasks;
    // 主线程管理阻塞信号
    bool_sig manager;
    // 回测宇宙·时间
    std::unordered_map<int, DateTime*> mBackTestTime;

    // 主线程
    void __MainFunc() {
        // hiden implementations
    }

    // 数据推送线程（由外部进行终止）
    void __DataSendFunc(int sid) {
        // hiden implementations
    };

public:
    /* 外部调用函数 */

    // 无参构造函数
    RealSimApi(): manager(0) {}

    void RegisterFront(char * frontAddr) {strcpy_s(this->frontAddr,frontAddr);}

    void RegisterSpi(SimMdSpi *) {this->spi = spi;}

    const char *GetApiVersion() {return this->apiVersion;}

    void Release() {
        // hiden implementation
    }

    void Init() {
        this->mainThread = new std::jthread(&RealSimApi::__MainFunc, this);
        this->mainThread->detach();
    }

    int Join() {
        // hiden implementation
    };

    const char * GetTradingDay() {
        //
    };

    int SubscribeMarketData(char * symbols[], int num, int sid) {
        // hiden implementations
    }

    int CompleteSubMarketData(int sid, const char * start, const char * end) {
        // hiden implementations
    }
};

SimMdApi * SimMdApi::CreateSimMdApi
(const char * pszFlowPath, const bool bIsUsingUdp, const bool bIsMulticast) {
    RealSimApi * api = new RealSimApi();
    return api;
}

