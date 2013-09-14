#ifndef PROGRESS_H_
#define PROGRESS_H_

typedef struct
{
    char*  name;
    double total;
    double now;
} p_entry;

void         progress_init();
void         progress_add( const char* name );
p_entry*     progress_get( const unsigned int idx );
unsigned int progress_count();
void         progress_update( const char* name, 
                              const double total, 
                              const double now );

#endif
