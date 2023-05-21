#ifndef DICT_H
#define DICT_H

#include <glib.h>

typedef struct s_dict {
	gunichar letter ;
	struct s_dict* alt ;
	struct s_dict* next ;
} dict_t ;

dict_t* dict_new() ;
void dict_free( dict_t* ) ;
dict_t* dict_insert( dict_t*, gunichar* ) ;
int dict_search( dict_t*, gunichar* ) ;
dict_t* build_dict_from_file( const gchar* filename ) ;

#endif
