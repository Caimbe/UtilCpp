#ifndef UTIL_HPP
#define UTIL_HPP

#include <iomanip>
#include <sstream>
#include <jsoncpp/json/json.h>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <chrono>
#include <ctime>

using namespace std;
using namespace std::chrono;
typedef duration<int, ratio_multiply<hours::period, ratio<24> >::type> days;

inline std::string to_string(const long double &_Val, const streamsize& precision)
{	// convert long double to string

    std::ostringstream out;
    out << std::fixed << std::setprecision(precision) << _Val;
    return out.str();
}

inline std::string to_string(const std::tm& tm, const char* format="%4d-%02d-%02d")
{
    std::tm _default = std::tm();
    if(difftime(mktime((std::tm*)&tm), mktime(&_default)) == 0)
        return "";

    char buffer[100];
    sprintf(buffer, format, tm.tm_year+1900, tm.tm_mon+1, tm.tm_mday);

    return buffer;
}

inline std::tm stotm(const string& str, const string& format = "%Y-%m-%d")
{
    struct std::tm tm = {0};
    if(str.size()){
        boost::gregorian::date date(boost::gregorian::from_string(str));
        tm = boost::gregorian::to_tm(date);
    }
    return tm;
}

inline system_clock::time_point to_chrono(const std::tm& tm)
{
    time_t time_t = mktime((std::tm*)&tm);
    system_clock::time_point chrono = system_clock::from_time_t(time_t);

    return chrono;
}

inline days to_chrono_day(const system_clock::time_point& time_point)
{
    days d = duration_cast<days>(time_point.time_since_epoch() );
    return d;
}

inline days to_chrono_day(const std::tm& tm)
{
    system_clock::time_point point = to_chrono(tm);
    days d = duration_cast<days>(point.time_since_epoch() );
    return d;
}


#if _MSC_VER || __MINGW32__
#   include <sys/stat.h>
#	define makedir(x) mkdir(x)
#else
#	define makedir(x) mkdir(x, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH)
#endif

#endif // UTIL_HPP
