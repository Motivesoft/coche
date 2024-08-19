#pragma once

#include <functional>
#include <map>
#include <string>

class uci
{
public:
    uci()
    {
        functionMap["quit"] = std::bind( &uci::command_quit, this, std::placeholders::_1 );
        // Nothing to do
    }

    virtual ~uci()
    {
        // Nothing to do
    }

    bool process( const std::string& command );

    static std::string name()
    {
        return "coche";
    }

    static std::string author()
    {
        return "Motivesoft";
    }

    static std::string description()
    {
        return "A UCI chess engine";
    }

    static std::string version()
    {
        return "0.0.1";
    }

private:
    bool command_quit( const std::string& arguments );

    std::map<std::string, std::function<bool( const std::string& )>> functionMap;
};

