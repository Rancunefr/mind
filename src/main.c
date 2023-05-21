#include <stdio.h>
#include <locale.h>
#include "dict.h"

int main( int argc, char** argv, char** envv ) {

	dict_t* dictionnaire ;

	setlocale(LC_ALL, "") ;

	dictionnaire = build_dict_from_file( "dict.fr" ) ;

	printf( "coucou : %d\n", dict_search( dictionnaire, "coucou" ) ) ;
	printf( "chienne : %d\n", dict_search( dictionnaire, "chienne" ) ) ;
	printf( "chienn : %d\n", dict_search( dictionnaire, "chienn" ) ) ;
	printf( "chiot : %d\n", dict_search( dictionnaire, "chiot" ) ) ;
	
	dict_free( dictionnaire ) ;
	return 0 ;
}
