#include "progress.h"

#include <ncurses.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "output.h"

#define ENTRIES_INITIAL_CAPACITY 10

static p_entry**    entries;
static unsigned int entries_capacity;
static unsigned int entries_count;
static sem_t        sem_progress;

static void sort_progress_entries();

//
// progress_init
//
// Initialize the progress list.
//
void progress_init()
{
    entries_capacity = ENTRIES_INITIAL_CAPACITY;
    entries_count = 0;
    entries = malloc( ENTRIES_INITIAL_CAPACITY * sizeof( p_entry* ) );

    if ( entries == NULL )
    {
        printf( "error allocating the progress entries list\n" );
        exit( 1 );
    }

    sem_init( &sem_progress, 0, 1 );
}

//
// progress_add
//
// Add NAME to the list of progress entries.
//
void progress_add( const char* name )
{
    if ( name == NULL ) return;

    // wait for a semaphore since multiple threads may do this at once
    sem_wait( &sem_progress );

    if ( entries_count == entries_capacity )
    {
        entries = realloc( entries, sizeof( char* ) * entries_capacity * 2 );

        if ( entries == NULL )
        {
            output( "error reallocating the progress entries list\n" );
            exit( 1 );
        }

        entries_capacity *= 2;
    }

    p_entry* e = malloc( sizeof( p_entry ) );

    if ( e == NULL )
    {
        output( "error allocating new progress entry\n" );
        exit( 1 );
    }

    e->name = malloc( ( strlen( name ) + 1 ) * sizeof( char ) );

    if ( e->name == NULL )
    {
        output( "error allocating new progress entry name\n" );
        exit( 1 );
    }

    strcpy( e->name, name );
    e->total = 0.0;
    e->now = 0.0;

    entries[entries_count++] = e;

    sort_progress_entries();

    sem_post( &sem_progress );
}

//
// progress_get
//
// Return a pointer to the entry stored at index IDX.
//
p_entry* progress_get( const unsigned int idx )
{
    if ( idx >= entries_count ) return NULL;

    return entries[idx];
}

//
// progress_count
//
// Return the number of entries in the progress list.
//
unsigned int progress_count()
{
    return entries_count;
}

//
// progress_update
//
// Update the TOTAL and NOW values of the progress entry with name NAME.
//
void progress_update( const char* name, const double total, const double now )
{
    if ( name == NULL ) return;
    if ( total < 0.0 ) return;
    if ( now < 0.0 ) return;

    int x;
    p_entry* e;
    for ( x = 0; x < entries_count; x++ )
    {
        e = entries[x];
        if ( strcmp( e->name, name ) == 0 )
        {
            e->total = total;
            e->now = now;
        }
    }
}

//
// sort_progress_entries
//
// Sort the entries array alphabetically.
//
static void sort_progress_entries()
{
    int x, y;

    for ( x = 0; x < entries_count; x++ )
    {
        for ( y = x + 1; y < entries_count; y++ )
        {
            if ( strcmp( entries[x]->name, entries[y]->name ) > 0 )
            {
                p_entry* tmp = entries[x];
                entries[x] = entries[y];
                entries[y] = tmp;
            }
        }
    }
}
