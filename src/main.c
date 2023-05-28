#include <stdio.h>
#include <locale.h>

#include "dict.h"
#include "document.h"
#include "pdf.h"

#define NB_DICTS 2

dict_t* dicts[NB_DICTS] ;


int main( int argc, char** argv, char** envv ) {

	setlocale(LC_ALL, "") ;

	dicts[LANG_EN] = dict_build_from_file( "./dict.en" ) ;
	dicts[LANG_FR] = dict_build_from_file( "./dict.fr" ) ;

	printf( "%d \n", dict_count( dicts[LANG_FR]) ) ;
	printf( "%d \n", dict_count( dicts[LANG_EN]) ) ;

	load_pdf( argv[1] ) ;

	dict_free( dicts[LANG_EN] ) ;
	dict_free( dicts[LANG_FR] ) ;

	return 0 ;
}
