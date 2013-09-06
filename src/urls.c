#include "urls.h"

#include <stdlib.h>
#include <string.h>

#define LIST_INITIAL_CAPACITY 10

static unsigned int count;
static unsigned int capacity;
static char**       list;

void url_init()
{
    count = 0;
    capacity = LIST_INITIAL_CAPACITY;
    list = malloc( LIST_INITIAL_CAPACITY * sizeof( char* ) );
}

void url_add( const char* url )
{
    if ( count == capacity )
    {
        list = realloc( list, sizeof( char* ) * capacity * 2 );
        capacity *= 2;
    }

    list[count] = malloc( sizeof( char ) * strlen( url ) );
    memcpy( list[count], url, strlen( url ) );
    count++;
}

const char* url_get( const unsigned int i )
{
    return list[i];
}

unsigned int  url_count()
{
    return count;
}
