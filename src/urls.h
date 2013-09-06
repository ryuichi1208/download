#ifndef URL_H_
#define URL_H_

void         url_init();
void         url_add( const char* url );
const char*  url_get( const unsigned int i );
unsigned int url_count();

#endif
