#include "board.h"

board::board( const std::string& fen )
{

}

/**
 * Populate the supplied vector with moves and return the count
 */
size_t board::get_moves( std::vector<move_t>& moves )
{
    moves.push_back( move::from_string( "e2e4" ) );
    moves.push_back( move::from_string( "e7e8b" ) );
    moves.push_back( move::from_string( "d1d2r" ) );
    moves.push_back( move::from_string( "h4f6q" ) );
    moves.push_back( move::from_string( "c1a8n" ) );

    return moves.size();
}

/**
 * Make 'move' on the board and return an undo object
 */
uint32_t board::make_move( move_t move )
{
    return 0;
}

/**
 * Unmake a move on the board by applying the 'undo' object
 */
uint32_t board::unmake_move( move_t move )
{
    return 0;
}
