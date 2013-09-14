#include "output.h"

#include <ncurses.h>
#include <semaphore.h>
#include <stdbool.h>

#include "progress.h"

// if true, use ncurses to show live download progress
static bool show_progress;

// semaphore to manage multi-thread text output
static sem_t sem_output;

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
        sem_init( &sem_output, 0, 1 );
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
        sem_destroy( &sem_output );
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
    if ( !sem_trywait( &sem_output ) ) return;

    clear();

    int x;
    p_entry* e;
    for ( x = 0; x < progress_count(); x++ )
    {
        e = progress_get( x );
        mvprintw( 0 + x, 0, "|%s|: |%g/%g|\n", e->name, e->now, e->total );
    }

    refresh();
    sem_post( &sem_output );
}
