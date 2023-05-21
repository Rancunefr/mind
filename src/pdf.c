#include <stdio.h>
#include <glib/poppler.h>
#include <locale.h>
#include <string.h>
#include "dict.h"

gint g_unichar_strlen( gunichar* text ) {
	gint j = 0 ;
	while ( text[j] != L'\0' )
		j++ ;
	return j ;
}


gunichar* get_next_word( gunichar* text, gunichar** word ) {
	if ( *text == L'\0' ) {
		*word = NULL ;
		return text ;
	}
	*word = text ;
	while ( g_unichar_isspace(**word) ) {
		(*word)++ ;
	}
	text = (*word) + 1 ;
	while( (!g_unichar_isspace( *text )) && (*text != U'\0') ) {
		text++ ;
	}
	if ( *text != U'\0' ) {
		*text = L'\0' ;
		text++ ;
	}
	return text ;
}

void process_word( gunichar* mot ) {
	gunichar* fin ;
	gunichar* tmp ;
	while( (!g_unichar_isalnum(*mot)) &&( *mot != U'\0' ) )
		mot++ ;
	fin = mot + g_unichar_strlen( mot ) - 1 ;
	while( (!g_unichar_isalnum(*fin)) &&( fin != mot ) )
		fin-- ;
	*(fin + 1) = U'\0' ;

	for ( tmp = mot; tmp <= fin; tmp++ )
		*tmp = g_unichar_tolower ( *tmp ) ;

	if ( g_unichar_strlen( mot ) < 2 ) {
		printf ("XX \n") ;
		return ;
	}

	// TODO: INDEXATION

}

void process_text( gunichar* text ) {
	gunichar* cpy ;
	gunichar* mot ;
	cpy = get_next_word( text, &mot ) ;
	while ( mot != NULL ) {
		process_word( mot ) ;
		cpy = get_next_word( cpy, &mot ) ;
	} 
}



int main( int argc, char** argv, char** envv ) {
	
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
