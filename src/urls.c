#include "urls.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "output.h"

#define URLS_INITIAL_CAPACITY 10

static char**       urls;
static unsigned int urls_capacity;
static unsigned int urls_count;

//
// url_init
//
// Initialize the list of URLs (empty list with a default capacity).
//
void url_init()
{
    urls_count = 0;
    urls_capacity = URLS_INITIAL_CAPACITY;
    urls = malloc( URLS_INITIAL_CAPACITY * sizeof( char* ) );

    if ( urls == NULL )
    {
        printf( "error allocating URL list\n" );
        exit( 1 );
    }
}

//
// url_add
//
// Add the given URL to the list of URLs.
//
void url_add( const char* url )
{
    if ( url == NULL ) return;

    // grow the URL list if necessary
    if ( urls_count == urls_capacity )
    {
        urls = realloc( urls, sizeof( char* ) * urls_capacity * 2 );

        if ( urls == NULL )
        {
            output( "error reallocating URL list\n" );
            exit( 1 );
        }

        urls_capacity *= 2;
    }

    urls[urls_count] = malloc( ( strlen( url ) + 1 ) * sizeof( char ) );

    if ( urls[urls_count] == NULL )
    {
        output( "error allocating new URL\n" );
        exit( 1 );
    }

    memcpy( urls[urls_count], url, strlen( url ) + 1 );
    urls_count++;
}

//
// url_get
//
// Return the Ith URL in the list of URLs.
//
const char* url_get( const unsigned int i )
{
    if ( i >= urls_count ) return NULL;

    return urls[i];
}

//
// url_count
//
// Return the number of URLs stored in the list of URLs.
//
unsigned int url_count()
{
    return urls_count;
}
