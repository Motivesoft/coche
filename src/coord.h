#pragma once

#include <stdint.h>
#include <string>

// Helper methods for working with coordinates - squares, moves, pieces

// TODO decide if we want to rename this

typedef uint8_t index_t;
typedef uint8_t piece_t;

class coord
{
public:
    // Note that here, we are treating a1 through h8 as:
    // a1 == 0, b1 == 1, c1 == 2, ..., h1 == 7, a8 == 56, b8 == 57, c8 == 58, ..., h8 == 63

    static std::string coord_to_algebraic( index_t rank, index_t file )
    {
        return std::string( 1, 'a' + file ) + std::to_string( rank + 1 );
    }

    static std::string index_to_algebraic( index_t index )
    {
        return coord_to_algebraic( index / 8, index % 8 );
    }

    static index_t algebraic_to_index( const std::string& algebraic )
    {
        return ( ( algebraic[ 1 ] - '1' ) * 8 ) + ( algebraic[ 0 ] - 'a' );
    }
};