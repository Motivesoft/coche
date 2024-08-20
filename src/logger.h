#pragma once

#include <string>

class logger
{
    // Keep these in the header file
    // 
    // These are not necessarily fast methods. Typically, surround calls to these methods with a "#ifdef _DEBUG" block 
    // so they get compiled out in release builds but then use them as-is for special situations during development if required

public:
    template <typename T, typename... Args>
    inline static void debug( T&& first, Args&&... args )
    {
        log( "DEBUG", first, std::forward<Args>( args )... );
    }

    template <typename T, typename... Args>
    inline static void info( T&& first, Args&&... args )
    {
        log( "INFO ", first, std::forward<Args>( args )... );
    }

    template <typename T, typename... Args>
    inline static void warn( T&& first, Args&&... args )
    {
        log( "WARN ", first, std::forward<Args>( args )... );
    }

    template <typename T, typename... Args>
    inline static void error( T&& first, Args&&... args )
    {
        log( "ERROR", first, std::forward<Args>( args )... );
    }

private:
    template <typename T, typename... Args>
    inline static void log( const char* level, T&& first, Args&&... args )
    {
        std::fprintf( stderr, "%s | %s | ", timestamp().c_str(), level );
        std::fprintf( stderr, first, std::forward<Args>( args )... );
        std::fprintf( stderr, "\n" );
    }

    // Implemented here, rather than in utility.h to avoid circular dependencies

    static std::string timestamp();
};

