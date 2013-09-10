#include "output.h"

#include <ncurses.h>
#include <stdbool.h>

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
