#include <getopt.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

#include "urls.h"

static void  parse_arguments( const int argc, char* const* argv );
static void  parse_file( const char* filename );
static void* download_url( void* url );
static FILE* get_output_file( const char* url );

static const char* argument_list = "f:q";
static char*       url_filename = NULL;
static bool        quiet = false;
static char**      remaining_arguments = NULL;

//
// main
//
// Begin program execution with the given argument list ARGV of length ARGC.
//
int main( int argc, char** argv )
{
    url_init();
    parse_arguments( argc, (char* const*) argv );

    if ( url_filename != NULL )
    {
        parse_file( url_filename );
    }

    pthread_t tid[url_count()];
    curl_global_init( CURL_GLOBAL_ALL );

    int x;
    for ( x = 0; x < url_count(); x++ )
    {
        pthread_create( &tid[x], NULL, download_url, (void*) url_get( x ) );
    }
    for ( x = 0; x < url_count(); x++ )
    {
        pthread_join( tid[x], NULL );
    }

    return 0;
}

//
// parse_arguments
//
// Given the standard set of arguments (ARGV) of length ARGC, record the
// supplied program inputs.
//
static void parse_arguments( const int argc, char* const* argv )
{
    int o;
    while ( ( o = getopt( argc, argv, argument_list ) ) != -1 )
    {
        switch( o )
        {
            case 'f':
                url_filename = optarg;
                break;
            case 'q':
                quiet = true;
                break;
            default:
                exit( 1 );
                break;
        }
    }

    if ( optind < argc )
    {
        remaining_arguments = (char**) argv + optind;
    }

    printf( "arguments:\n" );
    printf( "    url_filename = %s\n", url_filename );
    printf( "    quiet = %s\n", quiet ? "true" : "false" );

    // add the trailing urls
    // (This only works properly with GNU getopt, because it sorts the argument
    // list to put the loose arguments at the end.  BSD getopt does not do 
    // this!)
    int i;
    for ( i = 0; i < argc - optind; i++ )
    {
        printf( "    %s\n", remaining_arguments[i] );
        url_add( remaining_arguments[i] );
    }
}

//
// parse_file
//
// Open the FILENAME file and read in the list of URLs.
//
static void parse_file( const char* filename )
{
    FILE* f = fopen( filename, "r" );
    if ( f == NULL )
    {
        printf( "error opening %s\n", filename );
        exit( 1 );
    }

    char line[256];
    while ( fgets( line, 255, f ) != 0 )
    {
        line[strlen( line ) - 1] = '\0'; // ensure last character is null
        url_add( line );
    }
}

//
// download_url
//
// Download the data at the given URL.  This function is passed to 
// pthread_create as the execution callback.
//
static void* download_url( void* url )
{
    CURL *curl;

    curl = curl_easy_init();
    curl_easy_setopt( curl, CURLOPT_URL, url );
    curl_easy_setopt( curl, CURLOPT_WRITEDATA, get_output_file( (char*) url ) );
    curl_easy_perform( curl ); /* ignores error */ 
    curl_easy_cleanup( curl );
 
    return NULL;
}

//
// get_output_file
//
// Given the URL name, open and return file for writing.  The name of the opened
// file is based off the URL:  from right to left, the longest string not
// containing a '/' character.
//
static FILE* get_output_file( const char* url )
{
    // starting at the end, walk a pointer backwards until either a '/'
    // character is encountered, or the beginning of the string is passed
    int i = strlen( url ) - 1;
    char* p = (char*) ( url + i );
    while ( i >= 0 )
    {
        if ( *p == '/' )
        {
            break;
        }
        p--;
        i--;
    }
    p++;

    // then open a file for writing and return
    FILE* f = fopen( p, "w" );
    if ( f == NULL )
    {
        printf( "error opening %s\n", p );
        exit( 1 );
    }

    return f;
}
