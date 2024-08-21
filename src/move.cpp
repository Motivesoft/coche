#include "move.h"

#include "coord.h"

std::string move::to_string( const move_t move )
{
    if ( move::is_promotion( move ) )
    {
        char promotionPiece = '\0';
        switch ( move & promotion_piece_mask )
        {
            case promotion_piece_knight:
                promotionPiece = 'n';
                break;
            case promotion_piece_bishop:
                promotionPiece = 'b';
                break;
            case promotion_piece_rook:
                promotionPiece = 'r';
                break;
            case promotion_piece_queen:
                promotionPiece = 'q';
                break;
        }

        if( promotionPiece != '\0' )
        {
            return coord::index_to_algebraic( move::from_index( move ) ) + coord::index_to_algebraic( move::to_index( move ) ) + promotionPiece;
        }
    }

    return coord::index_to_algebraic( move::from_index( move ) ) + coord::index_to_algebraic( move::to_index( move ) );
}

move_t move::from_string( const std::string& move )
{
    auto from = coord::algebraic_to_index( move.substr( 0, 2 ) );
    auto to = coord::algebraic_to_index( move.substr( 2, 2 ) );

    if ( move.size() > 4 )
    {
        move_t promotionPiece = 0;
        switch ( move[ 4 ] )
        {
            case 'n':
                promotionPiece = promotion_piece_knight;
                break;

            case 'b':
                promotionPiece = promotion_piece_bishop;
                break;

            case 'r':
                promotionPiece = promotion_piece_rook;
                break;

            case 'q':
                promotionPiece = promotion_piece_queen;
                break;
        }

        return ( from << shift_distance_from ) | ( to << shift_distance_to ) | promotionPiece | move_type_promotion;
    }

    return ( from << shift_distance_from ) | ( to << shift_distance_to );
}
