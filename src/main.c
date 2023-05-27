#include <stdio.h>
#include <locale.h>

#include "dict.h"
#include "document.h"

#define NB_DICTS 2

dict_t* dicts[NB_DICTS] ;


int main( int argc, char** argv, char** envv ) {

	setlocale(LC_ALL, "") ;

	int* test= malloc( 50000*sizeof(int) ) ;

	dicts[LANG_EN] = dict_build_from_file( "./dict.en" ) ;
	dicts[LANG_FR] = dict_build_from_file( "./dict.fr" ) ;

	test[0] = dict_count( dicts[LANG_FR]) ;	
	test[1] = dict_count( dicts[LANG_FR]) ;	

	printf( "%d \n", test[0] ) ;
	printf( "%d \n", test[1] ) ;



	dict_free( dicts[LANG_EN] ) ;
	dict_free( dicts[LANG_FR] ) ;


	return 0 ;
}
