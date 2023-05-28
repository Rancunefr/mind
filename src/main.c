#include <stdio.h>
#include <locale.h>

#include "dict.h"
#include "document.h"
#include "pdf.h"

#define NB_DICTS 2

dict_t* dicts[NB_DICTS] ;


int main( int argc, char** argv, char** envv ) {

	setlocale(LC_ALL, "") ;
	document_t *doc ;

	doc = document_new( FILETYPE_PDF, argv[1], LANG_EN, NULL ) ;

	dicts[LANG_EN] = dict_build_from_file( "./dict.en" ) ;
	dicts[LANG_FR] = dict_build_from_file( "./dict.fr" ) ;

	printf( "%d \n", dict_count( dicts[LANG_FR]) ) ;
	printf( "%d \n", dict_count( dicts[LANG_EN]) ) ;

	load_pdf( doc ) ;

	dict_free( dicts[LANG_EN] ) ;
	dict_free( dicts[LANG_FR] ) ;

	document_free( doc) ;

	return 0 ;
}
