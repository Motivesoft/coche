#include "logger.h"

#include <chrono>
#include <iomanip>
#include <sstream>
#include <time.h>

std::string logger::timestamp()
{
    auto now = std::chrono::system_clock::now();

    // Convert to time_t to get calendar time
    std::time_t nowAsTimeT = std::chrono::system_clock::to_time_t( now );

    // Convert to milliseconds
    auto nowMs = std::chrono::duration_cast<std::chrono::milliseconds>(
        now.time_since_epoch() ) % 1000;

    // Format the time
    std::tm nowTm;
    localtime_s( &nowTm, &nowAsTimeT ); // Windows-specific, see localtime_r

    std::ostringstream oss;
    oss << std::put_time( &nowTm, "%Y-%m-%d %H:%M:%S" )
        << '.' << std::setfill( '0' ) << std::setw( 3 ) << nowMs.count();

    return oss.str();
}
