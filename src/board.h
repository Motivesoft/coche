#pragma once

#include <vector>

class board
{
public:
    board() = default;
    virtual ~board() = default;

    // Delete copy constructor and copy assignment operator
    board( const board& ) = delete;
    board& operator=( const board& ) = delete;

    /**
     * Populate the supplied vector with moves and return the count
     */
    size_t get_moves( std::vector<uint16_t>& moves );

    /**
     * Make 'move' on the board and return an undo object 
     */
    uint32_t make_move( uint16_t move );

    /**
     * Unmake a move on the board by applying the 'undo' object
     */
    uint32_t unmake_move( uint16_t move );
};