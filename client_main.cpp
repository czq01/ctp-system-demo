# include "engine.h"
# include "strategy.cpp"

#include <signal.h>

void info() {
    DWORD error = GetLastError();
    std::cout << "onexit: errorCode=" << error << std::endl;
}

void crash_handler(int sig)
{
    printf("crash_handler! sig is %d\n",sig);
    DWORD error = GetLastError();
    std::cout << "on crash exit: errorCode=" << error << std::endl;
    exit(-1);  //exit 会回调before_exit, 因为已经注册
}

void signal_exit_handler(int sig)
{
    printf("sig_handler! sig is %d\n",sig);
    DWORD error = GetLastError();
    std::cout << "on sig exit: errorCode=" << error << std::endl;
    exit(0);
}


int main(int argc, char const *argv[]) {
    // 策略实例化
    atexit(info);
    signal(SIGTERM, signal_exit_handler);
    signal(SIGINT, signal_exit_handler);
    signal(SIGSEGV, crash_handler);    // SIGSEGV，非法内存访问
    signal(SIGFPE, crash_handler);       // SIGFPE，数学相关的异常，如被0除，浮点溢出，等等
    signal(SIGABRT, crash_handler);     // SIGABRT，由调用abort函数产生，进程非正常退出

    Strategy_example * templete = new Strategy_example;
    Start(templete);
    return 0;
}

