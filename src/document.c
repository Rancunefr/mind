#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "document.h"


document_t *document_new( filetype_t filetype, 
		char* uri, 
		lang_t lang, 
		char** keywords ) {

	document_t *tmp ;
	tmp = malloc( sizeof( document_t ) ) ;
	if ( tmp == NULL ) {
		fprintf(stderr, "Malloc error\n" ) ;
		return NULL ;
	}

	tmp->type = filetype ;
	tmp->language = lang ;
	tmp->timestamp = time(NULL) ;
	tmp->uri = malloc( strlen( uri ) + 1 ) ;
	if ( tmp->uri == NULL ){
		fprintf(stderr, "Malloc error\n" ) ;
		return NULL ;
	}
	strncpy( tmp->uri, uri, strlen(uri) + 1 ) ;
	tmp->keywords = dict_new() ;
	tmp->candidates = dict_new() ;

	return tmp ;
}

void document_free( document_t* doc ) {
	free( doc ) ;
}
