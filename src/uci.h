#pragma once

#include <functional>
#include <map>
#include <string>

class uci
{
public:
    uci();

    virtual ~uci();

    bool process( const std::string& command );

    // Public static methods 

    static std::string name();

    static std::string author();

    static std::string description();

    static std::string version();

private:
    // Commands

    bool command_debug( const std::string& arguments );
    bool command_quit( const std::string& arguments );
    bool command_uci( const std::string& arguments );

    std::map<std::string, std::function<bool( const std::string& )>> functionMap;

    // Broadcast methods

    void send_info( const std::string& message );

    // Properties

    bool debugMode;
};

