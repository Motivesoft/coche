#include "perft.h"

#include <chrono>
#include <fstream>
#include <iostream>
#include <vector>

#include "fen.h"
#include "logger.h"
#include "move.h"
#include "utility.h"

void perft::run( const std::string& arguments )
{
    // Support the following syntaxes:
    // - perft [depth]         - perform a search using a depth and the standard start position
    // - perft [depth] [fen]   - perform a search using a depth and FEN string
    // - perft fen [fen]       - perform a search using a FEN string containing expected results
    // - perft file [filename] - perform searches read from a file as FEN strings containing expected results
    //
    // Any of the above commands may begin with '-divide' to indicate that the search should be divided

    // Work out the type of perft we're running

    std::string tokens( arguments );
    std::string type;
    std::tie( type, tokens ) = utility::tokenize( tokens );

    bool divide = false;
    if ( type == "-divide" )
    {
        divide = true;

        std::tie( type, tokens ) = utility::tokenize( tokens );
    }

    if ( utility::is_number( type ) )
    {
        // Depth, with or without FEN
        int depth = std::stoi( type );

        if ( tokens.empty() )
        {
            perft::runDepth( depth, divide );
        }
        else
        {
            perft::runDepth( depth, tokens, divide );
        }
    }
    else if ( type == "fen" )
    {
        if ( tokens.empty() )
        {
            logger::error( "Missing FEN" );
        }
        else
        {
            perft::runFen( tokens, divide );
        }
    }
    else if ( type == "file" )
    {
        if ( tokens.empty() )
        {
            logger::error( "Missing filename" );
        }
        else
        {
            perft::runFile( tokens, divide );
        }
    }
    else
    {
        logger::error( "Unknown perft command: %s", type.c_str() );
    }
}

void perft::runDepth( size_t depth, bool divide )
{
    runDepth( depth, fen::start_position, divide );
}

void perft::runDepth( size_t depth, const std::string& fen, bool divide )
{
    size_t result = execute( depth, fen, divide );

    std::printf( "  Depth: %3zu. Actual: %12zu\n", depth, result );
}

void perft::runFen( const std::string& fen, bool divide )
{
    execute( fen, divide );
}

void perft::runFile( const std::string& filename, bool divide )
{
    std::ifstream file;

    file.open( filename );

    if ( !file.is_open() )
    {
        logger::error( "Could not open input file: %s", filename.c_str() );
        return;
    }

    std::string input;
    while ( std::getline( file, input ) )
    {
        // Trim leading, trailing and contained whitespace
        input = utility::sanitize_string( input );

        // Allow blank lines and comments
        if ( input.empty() || input.starts_with( "#" ) )
        {
            continue;
        }

        // Run each line as a perft test. These lines are expected to contain their expected results and will report whether they succeed-
        execute( input, divide );
    }

    if ( file.is_open() )
    {
        file.close();
    }
}

size_t perft::execute( size_t depth, const std::string& fen, bool divide )
{
    board board;

    // This supposedly gives us up to nanosecond accuracy.
    auto start = std::chrono::high_resolution_clock::now();

    size_t nodes = search( depth, board, divide );

    auto end = std::chrono::high_resolution_clock::now();

    // TODO Report to the nanosecond for now, but if microsecond or millisecond is enough, change this
    std::chrono::duration<long long, std::nano> duration = end - start;

    auto nanos = std::chrono::duration_cast<std::chrono::nanoseconds>( duration ).count();
    auto millis = std::chrono::duration_cast<std::chrono::milliseconds>( duration ).count();

    // Convert to hh:mm:ss.nn
    static const long long nanosPerSecond = 1000LL * 1000LL * 1000LL;
    static const long long nanosPerMinute = 60LL * nanosPerSecond;
    static const long long nanosPerHour = 60LL * nanosPerMinute;

    auto hours = nanos / nanosPerHour;
    nanos %= nanosPerHour;

    auto minutes = nanos / nanosPerMinute;
    nanos %= nanosPerMinute;

    auto seconds = nanos / nanosPerSecond;
    nanos %= nanosPerSecond;

    // Print the duration in hours:minutes:seconds format
    std::printf( "Depth: %3zu. Nodes: %12zu. Time: %2lld:%02lld:%02lld.%09lld (%lld ms)\n", depth, nodes, hours, minutes, seconds, nanos, millis );

    return nodes;
}

void perft::execute( const std::string& fen, bool divide )
{
#ifdef _DEBUG
    logger::debug( "Processing: %s", fen.c_str() );
#endif

    // This is expected to contain a FEN string with expected results at the end, either comma or semi-colon separated
    std::string position;
    std::string results;
    
    // Collection of depths and expected counts
    std::vector<std::pair<size_t,size_t>> expectedResults;

    // Split the string on the first semi-colon
    std::tie(position, results) = utility::split( fen, ';' );

    if( results.empty() )
    {
        // Must be split the string with commas
        std::tie(position, results) = utility::split( fen, ',' );

        if( results.empty() )
        {
            // No results
            logger::error( "Missing results in FEN: %s", fen.c_str() );
            return;
        }

        // Format is along the lines of 
        // - FEN,10,20
        //
        // Assume that the sender got the format correct

        std::string result;

        size_t depth = 1;

        while ( !results.empty() )
        {
            // Split each semi-colon separated element from the input string
            std::tie( result, results ) = utility::split( results, ',' );

            // Add to the collection to be tested later
            if ( !result.empty() )
            {
                expectedResults.push_back( std::make_pair( depth, std::stoul( result ) ) );
            }

            // Increment the depth
            depth++;
        }
    }
    else
    {
        // Format is along the lines of 
        // - FEN;D1 10;D2 20
        //
        // Assume that the sender got the format correct
        // Other items are allowed in this same structure, so make sure we only take the ones starting with 'D'

        std::string result;
        std::string depth;
        std::string count;

        while ( !results.empty() )
        {
            // Split each semi-colon separated element from the input string
            std::tie( result, results ) = utility::split( results, ';' );

            // Trap anything malformed, e.g. FEN;;;
            if ( !result.empty() )
            {
                // Split each segment on the first space
                std::tie( depth, count ) = utility::split( result, ' ' );

                // Add to the collection to be tested later
                if ( depth[ 0 ] == 'D' )
                {
                    expectedResults.push_back( std::make_pair( std::stoul( depth.substr( 1 ) ), std::stoul( count ) ) );
                }
            }
        }
    }

    if ( !expectedResults.empty() )
    {
        std::printf( "FEN: %s\n", position.c_str() );

        // Now run the tests
        for ( auto it = expectedResults.cbegin(); it != expectedResults.cend(); it++ )
        {
            size_t result = execute( it->first, fen, divide );

            std::printf( "  Depth: %3zu. Expected: %12zu. Actual: %12zu. %s\n", it->first, it->second, result, ( it->second == result ? "PASSED" : "FAILED" ) );
        }
    }
#ifdef _DEBUG
    else
    {
        logger::debug( "Skipping line with no test results defined" );
    }
#endif
}

size_t perft::search( size_t depth, board& board, bool divide )
{
    if ( depth == 0 )
    {
        return 1;
    }

    size_t nodes = 0;

    std::vector<move_t> moves;
    moves.reserve( 256 );

    auto count = board.get_moves( moves );

    for ( auto it = moves.cbegin(); it != moves.cend(); it++ )
    {
        auto undo = board.make_move( *it );

        auto moveNodes = search( depth - 1, board, false );

        nodes += moveNodes;

        if ( divide )
        {
            std::printf( "  %s : %12zu\n", move::to_string( *it ).c_str(), moveNodes );
        }

        board.unmake_move( undo );
    }

    return nodes;
}
