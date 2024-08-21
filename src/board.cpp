#include "board.h"

/**
 * Populate the supplied vector with moves and return the count
 */
size_t board::get_moves( std::vector<uint16_t>& moves )
{
    moves.push_back( 0x0001 );
    return moves.size();
}

/**
 * Make 'move' on the board and return an undo object
 */
uint32_t board::make_move( uint16_t move )
{
    return 0;
}

/**
 * Unmake a move on the board by applying the 'undo' object
 */
uint32_t board::unmake_move( uint16_t move )
{
    return 0;
}
