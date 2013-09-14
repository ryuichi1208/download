#ifndef OUTPUT_H_
#define OUTPUT_H_

#include <stdbool.h>

void output_init( bool progress );
void output_end();
void output( const char* format, ... );
void output_print_progress();

#endif
