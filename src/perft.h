#pragma once

#include <string>

#include "board.h"

class perft
{
public:
    /**
     * Run a perft test based on the provided arguments string
     * 
     * Support the following:
     * - perft [depth]         - perform a search using a depth and the standard start position
     * - perft [depth] [fen]   - perform a search using a depth and FEN string
     * - perft fen [fen]       - perform a search using a FEN string containing expected results
     * - perft file [filename] - perform searches read from a file as FEN strings containing expected results
     * 
     * Any of the above commands may begin with '-divide' to indicate that the search should be divided
     */
    static void run( const std::string& arguments );

private:
    static void runDepth( size_t depth, bool divide );

    static void runDepth( size_t depth, const std::string& fen, bool divide );

    static void runFen( const std::string& fen, bool divide );

    static void runFile( const std::string& filename, bool divide );

    static size_t execute( size_t depth, const std::string& fen, bool divide );

    static void execute( const std::string& fen, bool divide );

    static size_t search( size_t depth, board& board, bool divide );
};
