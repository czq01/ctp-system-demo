#include <iostream>
using namespace std;

//日期组件
#include <boost/date_time/gregorian/gregorian.hpp>
using namespace boost::gregorian;

//时间组件
#include <boost/date_time/posix_time/posix_time.hpp>
using namespace boost::posix_time;

int main()
{
    //起始时间
    ptime p1 = time_from_string("2000-01-01 00:00:01");
    //结束时间
    ptime p2(date(2000, 1, 2)); // 默认是 2000-01-01 23:59:59.999;

    //产生一个时间范围,   类似 日期范围  date_period的用法
    time_period tp(p1, p2); //  p2>p1才可以
    cout << tp << endl;

    time_duration td = tp.length(); //返回时间长度
    cout << td << endl;

    //把时间范围向后平移9秒
    tp.shift(seconds(9));
    cout << tp << endl;

    //把时间范围向两边扩大1小时
    tp.expand(hours(1));
    cout << tp << endl;

    //某个时间是否在这个时间范围内
    ptime p3 = time_from_string("2010-01-01 00:00:01");
    cout << tp.contains(p3) << endl;

    //----------------------------------------------------------

    //类似日期迭代器year_iterator, month_iterator等，时间迭代器time_iterator
    ptime p4 = time_from_string("2000-01-01 00:00:01");
    time_iterator it(p4, seconds(10)); //以10秒为步长

    for (int i = 0; i < 3; ++i)
        ++it; //迭代器的移动不会影响p4的值

    cout << "时间迭代器向后移动30秒 " << *it << endl;

    time_iterator it2(p4, hours(24)); //以24小时为步长
    ++it2; //迭代器的移动不会影响p4的值
    cout << "时间迭代器向后移动24小时" << *it2 << endl;

    //日期时间格式化
    date d1 = day_clock::local_day();
    date_facet* pDF = new date_facet("%Y年%m月%d日 ");
    cout.imbue(locale(cout.getloc(), pDF)); //指定输出流的语言环境
    cout << d1 << endl;

    ptime t1 = microsec_clock::local_time();
    time_facet* pTF = new time_facet("%Y年%m月%d日%H:%M:%S%F");
    cout.imbue(locale(cout.getloc(), pTF)); //指定输出流的语言环境
    cout << t1 << endl;

    getchar();
    return 0;
}
