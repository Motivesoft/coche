#include "perft.h"

#include "fen.h"

void perft::runDepth( int depth, bool divide )
{
    runDepth( depth, fen::start_position, divide );
}

void perft::runDepth( int depth, const std::string& fen, bool divide )
{
    // TODO
}

void perft::runFen( const std::string& fen, bool divide )
{

}

void perft::runFile( const std::string& filename, bool divide )
{

}
