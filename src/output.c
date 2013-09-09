#include "output.h"

#include <ncurses.h>
#include <stdbool.h>

static bool show_progress;

void output_init( bool progress )
{
    show_progress = progress;
    initscr();
    raw();
}

void output_end()
{
    if ( show_progress )
    {
        endwin();
    }
}

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
