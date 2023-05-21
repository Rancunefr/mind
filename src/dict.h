#ifndef DICT_H
#define DICT_H

#include <glib.h>

typedef struct s_dict {
	gchar letter ;
	struct s_dict* alt ;
	struct s_dict* next ;
} dict_t ;

dict_t* dict_new() ;
void dict_free( dict_t* ) ;
dict_t* dict_insert( dict_t*, gchar* ) ;
int dict_search( dict_t*, gchar* ) ;
dict_t* build_dict_from_file( const gchar* filename ) ;

#endif
