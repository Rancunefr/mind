#include <string.h>
#include <stdio.h>
#include <glib/poppler.h>
#include "process.h"
#include "document.h"

document_t* load_pdf( document_t* doc ) {
	
	PopplerDocument *document ;
	PopplerPage *page ;
	gunichar* text;
	char* text_raw ;
	int num_pages ;
	int i ;
	
	document = poppler_document_new_from_file( 
			doc->uri, 
			NULL, NULL ) ;
	
	if (document == NULL) {
		printf("Failed to open file \n");
		document_free( doc ) ;
		return NULL ;
	}

	num_pages = poppler_document_get_n_pages( document ) ;

	// Metadata

	gchar* metadata = poppler_document_get_metadata ( document ) ;
	text = g_utf8_to_ucs4( metadata, -1, NULL, NULL, NULL ) ;
	process_text( text, TXT_Metadata, doc ) ;
	g_free(text) ;
	g_free( metadata ) ;

	gchar* subject = poppler_document_get_subject ( document ) ;
	text = g_utf8_to_ucs4( subject, -1, NULL, NULL, NULL ) ;
	process_text( text, TXT_Subject, doc ) ;
	g_free(text) ;
	g_free( subject ) ;

	gchar* title = poppler_document_get_title ( document ) ;
	text = g_utf8_to_ucs4( title, -1, NULL, NULL, NULL ) ;
	process_text( text, TXT_Title, doc ) ;
	g_free(text) ;
	g_free(title) ;

	gchar* keywords = poppler_document_get_keywords( document ) ;
	text = g_utf8_to_ucs4(keywords, -1, NULL, NULL, NULL ) ;
	process_text( text, TXT_Keyword, doc ) ;
	g_free(text) ;
	g_free( keywords ) ;


	gchar* author = poppler_document_get_author( document ) ;
	text = g_utf8_to_ucs4( author, -1, NULL, NULL, NULL ) ;
	process_text( text, TXT_Author, doc ) ;
	g_free(text) ;
	g_free( author ) ;
	
	// Contenu

	for (i=0; i<num_pages; i++) {
		page = poppler_document_get_page( document, i ) ;
		text_raw = poppler_page_get_text( page ) ;
		text = g_utf8_to_ucs4( text_raw, -1, NULL, NULL, NULL ) ;
		process_text( text, TXT_Content, doc ) ;
	    g_free(text) ;
		g_free(text_raw) ;
		g_object_unref(page) ;
	}

	// images ? TODO

	g_object_unref(document) ;

	return doc ;
}
