#pragma once

#include <string>
#include <vector>

#include "move.h"

class board
{
public:
    board( const std::string& fen );

    virtual ~board() = default;

    // Delete copy constructor and copy assignment operator
    board( const board& ) = delete;
    board& operator=( const board& ) = delete;

    /**
     * Populate the supplied vector with moves and return the count.
     */
    size_t get_moves( std::vector<move_t>& moves );

    /**
     * Make 'move' on the board and return an undo object 
     */
    uint32_t make_move( move_t move );

    /**
     * Unmake a move on the board by applying the 'undo' object
     */
    uint32_t unmake_move( move_t move );
};