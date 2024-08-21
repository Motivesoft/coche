#pragma once

#include <string>

#include "coord.h"

// Define move_t to represent a move without the 'expense' of it being a class:
// - from square (6 bits for index)
// - to square (6 bits for index)
// - promotion piece (2 bits for knight, bishop, rook, queen)
// - 2 bits spare, assuming we don't need them for either promotion, castling, enpassant, check, capture, checkmate...
//
// Note that as move_t is fundamentally and integer type, we might be able to use it for sorting
// if it becomes rich enough to contain move type information - e.g. top bit being for capture, check or a terminal move

typedef uint16_t move_t;

class move
{
public:
    static std::string to_string( move_t move );

    static move_t from_string( const std::string& move );

private:
    inline static bool is_promotion( const move_t move ) 
    { 
        return ( move & move_type_mask ) == move_type_promotion;
    }

    inline static index_t from_index( const move_t move )
    {
        return ( move & index_from_mask ) >> shift_distance_from;
    }

    inline static index_t to_index( const move_t move )
    {
        return (move & index_to_mask) >> shift_distance_to;
    }

    // Masks
    inline static const move_t move_type_mask          = 0b1100000000000000;
    inline static const move_t promotion_piece_mask    = 0b0011000000000000;
    inline static const move_t index_from_mask         = 0b0000000000111111;
    inline static const move_t index_to_mask           = 0b0000111111000000;

    // Inverse masks
    inline static const move_t move_type_inverse       = ~move_type_mask;
    inline static const move_t promotion_piece_inverse = ~index_from_mask;
    inline static const move_t index_from_inverse      = ~index_from_mask;
    inline static const move_t index_to_inverse        = ~index_to_mask;

    // Shift distances - how far to shift a move to get the interesting bits to the lsb, if needed
    inline static const move_t shift_distance_from            = 0;
    inline static const move_t shift_distance_coords          = 3;
    inline static const move_t shift_distance_to              = 6;
    inline static const move_t shift_distance_promotion_piece = 12;
    inline static const move_t shift_distance_move_type       = 14;

    // Constants
    inline static const move_t move_type_normal       = 0b0000000000000000;
    inline static const move_t move_type_promotion    = 0b0100000000000000;
    inline static const move_t move_type_capture      = 0b1000000000000000;
    inline static const move_t move_type_unused       = 0b1100000000000000;

    inline static const move_t promotion_piece_knight = 0b0000000000000000;
    inline static const move_t promotion_piece_bishop = 0b0001000000000000;
    inline static const move_t promotion_piece_rook   = 0b0010000000000000;
    inline static const move_t promotion_piece_queen  = 0b0011000000000000;
};