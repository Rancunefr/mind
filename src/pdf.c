#include <string.h>
#include <stdio.h>
#include <glib/poppler.h>
#include "process.h"

int load_pdf( int argc, char** argv, char** envv ) {
	
	PopplerDocument *document ;
	PopplerPage *page ;
	gunichar* text;
	char* text_raw ;
	int num_pages ;
	int i ;
	int k ;
	long int j ;

	document = poppler_document_new_from_file( 
			argv[1], 
			NULL, NULL ) ;
	if (document == NULL) {
		printf("Failed to open file \n");
		return 1 ;
	}

	num_pages = poppler_document_get_n_pages( document ) ;

	// Metadata
/*
	gchar* metadata = poppler_document_get_metadata ( document ) ;
	printf("Metadata: %s \n", metadata ) ;

	gchar* subject = poppler_document_get_subject ( document ) ;
	printf("Subject: %s \n", subject) ;

	gchar* title = poppler_document_get_title ( document ) ;
	printf("Title: %s \n", title) ;

	gchar* keywords = poppler_document_get_keywords( document ) ;
	printf("Keywords: %s\n", keywords) ;

	gchar* author = poppler_document_get_author( document ) ;
	printf("Author: %s\n", author) ;
*/	
	// Contenu

	for (i=0; i<num_pages; i++) {
		page = poppler_document_get_page( document, i ) ;
		text_raw = poppler_page_get_text( page ) ;
		text = g_utf8_to_ucs4( text_raw, -1, NULL, NULL, NULL ) ;
		process_text( text ) ;
	}


	// images ? TODO


	// poppler_document_free(document) ; FIXME

	return 0 ;
}
