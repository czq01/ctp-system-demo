#ifndef _DATETIME_H_
#define _DATETIME_H_
#include <chrono>
#include <cstdio>
#include <format>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <time.h>

class Date {
private:
    mutable char cdt[20];
public:
    int year, month, day, wday;
    Date();
    Date(int year, int month, int day);
    // YYYY-MM-DD
    Date(const std::string&);
    // YYYY-MM-DD
    Date(const char*);
    bool IsLeapyYear(int year);
    int GetMonthDays(int year, int month);
    const char * toString();
    const char * toString(const char *);
    [[nodiscard]] int getwday();
    [[nodiscard]] bool isWeekDay();
    // 当前日期days天后是什么日期
    Date operator+(int days);
    // 当前日期days天前是什么日期
    Date operator-(int days);
    // 两个日期之间差了多少天？
    int operator-(const Date& d);
    // 日期比大小
    bool operator>(const Date& d) const;
    bool operator<(const Date& d) const;
    bool operator==(const Date& d) const;
    bool operator!=(const Date& d) const;
    Date& operator=(const Date& d);
    // 重载取地址符号
    Date* operator&();
    // 前置++
    Date& operator++();
    // 后置++
    Date operator++(int);
    // 前置--
    Date& operator--();
    // 后置++
    Date operator--(int);
    void operator()(const std::string&);
    friend std::ostream& operator<<(std::ostream& cout, const Date& d);
};

class Time {
private:
    mutable char cdt[18];
public:
    int hour, min, sec;
    int millsec;
    Time();
    // hh:mm:ss  ttt
    Time(const std::string& time, int millisec);
    Time(const int& hour, const int& min, const int& sec, const int& millsec);
    // hh:mm:ss  ttt
    Time(const std::string&);
    // hh:mm:ss  ttt
    Time(const char*);
    const char * toString();
    const char * toString(const char *);
    Time operator+(const Time&);
    Time operator+(int millisec);
    Time operator-(const Time&);
    Time operator-(int millisec);
    // 日期比大小
    bool operator>(const Time&) const;
    bool operator<(const Time&) const;
    bool operator==(const Time&) const;
    bool operator!=(const Time&) const;
    Time& operator=(const Time&);
    void operator()(const std::string&);
    // 重载取地址符号
    Time* operator&();
    friend std::ostream& operator<<(std::ostream& cout, const Time& d);
};

class DateTime {
private:
    tm* date_time = nullptr;
    mutable char cdt[30];

public:
    Date date;
    Time time;
    DateTime();
    // YYYY-MM-DD hh:mm:ss.ttt
    DateTime(const char*);
    // YYYY-MM-DD hh:mm:ss.ttt
    DateTime(const std::string&);
    // YYYYMMDD hh:mm:ss
    DateTime(const std::string& date, const std::string& time);
    // CTP: YYYYMMDD hh:mm:ss ttt
    DateTime(const std::string& date, const std::string& time, int millsec);
    DateTime(int year, int month, int day);
    DateTime(int year, int month, int day, int hour, int min, int sec, int millsec);
    DateTime(const DateTime&);
    const char * toString();
    ~DateTime();
    bool operator>(const DateTime&) const;
    bool operator<(const DateTime&) const;
    bool operator==(const DateTime&) const;
    bool operator!=(const DateTime&) const;
    void operator=(const DateTime&);
    void operator()(const std::string&);
    [[]] DateTime* now();
    friend std::ostream& operator<<(std::ostream& cout, const DateTime& d);
};
#endif