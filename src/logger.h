#pragma once

#include <string>

class logger
{
    // Keep these in the header file
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

    static std::string timestamp();
};

