#include "urls.h"

#include <stdlib.h>
#include <string.h>

#define LIST_INITIAL_CAPACITY 10

static unsigned int count;
static unsigned int capacity;
static char**       list;

//
// url_init
//
// Initialize the list of URLs (empty list with a default capacity).
//
void url_init()
{
    count = 0;
    capacity = LIST_INITIAL_CAPACITY;
    list = malloc( LIST_INITIAL_CAPACITY * sizeof( char* ) );
}

//
// url_add
//
// Add the given URL to the list of URLs.
//
void url_add( const char* url )
{
    // grow the URL list if necessary
    if ( count == capacity )
    {
        list = realloc( list, sizeof( char* ) * capacity * 2 );
        capacity *= 2;
    }

    list[count] = malloc( sizeof( char ) * strlen( url ) + 1 );
    memcpy( list[count], url, strlen( url ) + 1 );
    count++;
}

//
// url_get
//
// Return the Ith URL in the list of URLs.
//
const char* url_get( const unsigned int i )
{
    return list[i];
}

//
// url_count
//
// Return the number of URLs stored in the list of URLs.
//
unsigned int  url_count()
{
    return count;
}
