#pragma once

#include <functional>
#include <map>
#include <string>

class uci
{
public:
    uci( bool debug );

    virtual ~uci();

    bool process( const std::string& command );

    // Public static methods 

    static std::string name();

    static std::string author();

    static std::string description();

    static std::string version();

private:
    // Standard commands

    std::map<std::string, std::function<bool( const std::string& )>> functionMap;

    bool command_debug( const std::string& arguments );
    bool command_quit( const std::string& arguments );
    bool command_uci( const std::string& arguments );

    // Custom commands

    bool command_perft( const std::string& arguments );

    // Broadcast methods

    /**
     * Sends a formatted string to the caller via stdout.
     */
    template <typename T, typename... Args>
    inline static void send( T&& first, Args&&... args )
    {
        std::printf( first, std::forward<Args>( args )... );
        std::printf( "\n" );
    }

    /**
     * Sends an info string to the caller via stdout.
     */
    template <typename T, typename... Args>
    inline static void send_info_string( T&& first, Args&&... args )
    {
        send_info( "string", first, std::forward<Args>( args )... );
    }

    /**
     * Internal method, use one of the specialised send_info_xxx() methods.
     */
    template <typename T, typename... Args>
    inline static void send_info( const char* infoType, T&& first, Args&&... args )
    {
        std::printf( "info %s ", infoType );
        send( first, std::forward<Args>( args )... );
    }

    // Properties

    bool debugMode;
};

