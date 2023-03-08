#ifndef CTP_ENGINE_H
#define CTP_ENGINE_H

#include <functional>
#include <thread>
#include <format>

#include "WinSock2.h"
#include "base.h"
#include "convert.h"
#include "templete.h"

class Engine {
protected:
public:
    virtual void start() = 0;
    virtual void recvData() = 0;
    virtual int sendData(std::string, char) = 0;
    virtual void subMarketData(std::string& symbol, std::string& exchange) = 0;

    virtual void unSubMarketData(int &sid, std::string &symbol,
                                 std::string &exchange) = 0;

    virtual void sendOrder(char orderType, std::string wayType,
                           float price, int volume, std::string symbol,
                           std::string exchange, std::string investor,
                           bool stop) = 0;

    virtual void cancelOrder(std::string vtOrderID) = 0;

    virtual std::vector<Bar> getKLineData(std::string symbol,
                                          std::string exchange) = 0;
};

class CTAEngine : public Engine {
    /**
     * @brief 客户端及策略引擎
     *
     */
protected:
    std::vector<std::string> dataToSend;
    std::vector<Bar> getKLineData();
    bool hasSid = false;
    Templete * templete;
    int sid;
    std::queue<char> * qMethodQueue;
    std::queue<char *> * qEventQueue;
    std::binary_semaphore sig;
    void registerSID();
    void recvData() override;
    void onEvent();
    MemoryPool_Event eventPool;

public:
    CTAEngine(Templete * p);
    ~CTAEngine();
    void start();
    void subMarketData(std::string& symbol, std::string& exchange) override;

    void unSubMarketData(int &sid, std::string &symbol,
                         std::string &exchange) override;

    void sendOrder(char orderType, std::string wayType, float price,
                   int volume, std::string symbol, std::string exchange,
                   std::string investor, bool stop) override;

    void cancelOrder(std::string vtOrderID) override;

    std::vector<Bar> getKLineData(std::string symbol,
                                  std::string exchange) override;

    int sendData(std::string dataToSend, char type) override;

};

void Start(Templete * strategy);

#endif  // CTP_ENGINE_H