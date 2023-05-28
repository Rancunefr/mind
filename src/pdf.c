#include <string.h>
#include <stdio.h>
#include <glib/poppler.h>
#include "process.h"

int load_pdf( char* uri ) {
	
	PopplerDocument *document ;
	PopplerPage *page ;
	gunichar* text;
	char* text_raw ;
	int num_pages ;
	int i ;
	int k ;
	long int j ;

	document = poppler_document_new_from_file( 
			uri, 
			NULL, NULL ) ;
	
	if (document == NULL) {
		printf("Failed to open file \n");
		return 1 ;
	}

	num_pages = poppler_document_get_n_pages( document ) ;

	// Metadata

	gchar* metadata = poppler_document_get_metadata ( document ) ;
	text = g_utf8_to_ucs4( metadata, -1, NULL, NULL, NULL ) ;
//  printf("Metadata: %s \n", metadata ) ;
	//process_text( text ) ;
	g_free(text) ;
	g_free( metadata ) ;

	gchar* subject = poppler_document_get_subject ( document ) ;
	text = g_utf8_to_ucs4( subject, -1, NULL, NULL, NULL ) ;
//  printf("Subject: %s \n", subject) ;
	//process_text( text ) ;
	g_free(text) ;
	g_free( subject ) ;

	gchar* title = poppler_document_get_title ( document ) ;
	text = g_utf8_to_ucs4( title, -1, NULL, NULL, NULL ) ;
//  printf("Title: %s \n", title) ;
	//process_text( text ) ;
	g_free(text) ;
	g_free(title) ;

	gchar* keywords = poppler_document_get_keywords( document ) ;
	text = g_utf8_to_ucs4(keywords, -1, NULL, NULL, NULL ) ;
//  printf("Keywords: %s\n", keywords) ;
	//process_text( text ) ;
	g_free(text) ;
	g_free( keywords ) ;


	gchar* author = poppler_document_get_author( document ) ;
	text = g_utf8_to_ucs4( author, -1, NULL, NULL, NULL ) ;
//  printf("Author: %s\n", author) ;
	//process_text( text ) ;
	g_free(text) ;
	g_free( author ) ;
	
	// Contenu

	for (i=0; i<num_pages; i++) {
		page = poppler_document_get_page( document, i ) ;
		text_raw = poppler_page_get_text( page ) ;
		text = g_utf8_to_ucs4( text_raw, -1, NULL, NULL, NULL ) ;
		// process_text( text ) ;
	    g_free(text) ;
		g_free(text_raw) ;
		g_object_unref(page) ;
	}

	// images ? TODO

	g_object_unref(document) ;

	return 0 ;
}
