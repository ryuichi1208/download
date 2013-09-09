#ifndef PROGRESS_H_
#define PROGRESS_H_

void progress_init();
void progress_add( const char* name );
void progress_update( const char* name, const double total, const double now );
void progress_print();

#endif
