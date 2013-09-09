#include "progress.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ENTRIES_INITIAL_CAPACITY 10

typedef struct
{
    char*  name;
    double total;
    double now;
} p_entry;

static p_entry** entries;
static unsigned int entries_capacity;
static unsigned int entries_count;

void progress_init()
{
    entries_capacity = ENTRIES_INITIAL_CAPACITY;
    entries_count = 0;
    entries = malloc( ENTRIES_INITIAL_CAPACITY * sizeof( p_entry* ) );
}

void progress_add( const char* name )
{
    if ( entries_count == entries_capacity )
    {
        entries = realloc( entries, sizeof( char* ) * entries_capacity * 2 );
        entries_capacity *= 2;
    }

    p_entry* e = malloc( sizeof( p_entry ) );
    e->name = malloc( strlen( name ) * sizeof( char ) );
    strcpy( e->name, name );
    e->total = 0.0;
    e->now = 0.0;

    entries[entries_count++] = e;
}

void progress_update( const char* name, const double total, const double now )
{
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

void progress_print()
{
    int x;
    p_entry* e;
    for ( x = 0; x < entries_count; x++ )
    {
        e = entries[x];
        printf( "%s: %g/%g\n", e->name, e->now, e->total );
    }
}