#include "output.h"

#include <ncurses.h>
#include <stdbool.h>
#include <string.h>

#include "progress.h"

// if true, use ncurses to show live download progress
static bool show_progress;

//
// output_init
//
// Initialize the output system.  If PROGRESS is true, enable the ncurses
// system.
//
void output_init( bool progress )
{
    show_progress = progress;

    if ( show_progress )
    {
        initscr();
        raw();
    }
}

//
// output_end
//
// If necessary, close the ncurses system.
//
void output_end()
{
    if ( show_progress )
    {
        getch();
        endwin();
    }
}

//
// output
//
// Print the given FORMAT and variable argument list (...), either via printf or
// ncurses as appropriate.
//
void output( const char* format, ... )
{
    va_list arglist;
    va_start( arglist, format );

    if ( show_progress )
    {
        vwprintw( stdscr, format, arglist );
        refresh();
    }
    else
    {
        vprintf( format, arglist );
    }

    va_end( arglist );
}

//
// output_print_progress
//
// Print the current status of each file download.
// 
void output_print_progress()
{
    clear();

    int x;
    p_entry* e;

    // get max label length
    int max_label_length = 0;
    for ( x = 0; x < progress_count(); x++ )
    {
        e = progress_get( x );
        int length = strlen( e->name );

        if ( max_label_length < length )
        {
            max_label_length = length;
        }
    }

    // print the download progress for each entry
    for ( x = 0; x < progress_count(); x++ )
    {
        e = progress_get( x );

        // calculate the current download percentage and avoid NaN, as e->total
        // is initially zero
        double percentage;
        if ( e->total > 0.0 )
        {
            percentage = e->now / e->total * 100.0;
        }
        else
        {
            percentage = 0.0;
        }

        mvprintw( 0 + x, 0, "%s", e->name );

        // print extra spaces to align all the percentages
        int i = strlen( e->name );
        while ( i++ < max_label_length ) printw( " " );
        printw( ":" );
        if ( percentage < 100.0 ) printw( " " );
        if ( percentage < 10.0  ) printw( " " );

        printw( " %.2f%%\n", percentage );
    }

    refresh();
}
