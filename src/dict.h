#ifndef DICT_H
#define DICT_H

#include <glib.h>

typedef struct s_dict {
	gunichar letter ;
	struct s_dict* alt ;
	struct s_dict* next ;
} dict_t ;

dict_t* dict_new() ;
dict_t* dict_build_from_file( const gchar* filename ) ;

void dict_free( dict_t* ) ;

dict_t* dict_insert( dict_t*, gunichar* ) ;
dict_t* dict_insert_char( dict_t*, const char* ) ;

int dict_search( dict_t*, gunichar* ) ;
int dict_search_char( dict_t*, const char* ) ;

void dict_display( dict_t* ) ;
int  dict_count( dict_t* ) ;

#endif
