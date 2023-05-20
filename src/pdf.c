#include <stdio.h>
#include <glib/poppler.h>

int main( int argc, char** argv, char** envv ) {
	
	PopplerDocument *document ;
	PopplerPage *page ;
	char* text;
	int num_pages ;
	int i ;

	document = poppler_document_new_from_file( 
			argv[1], 
			NULL, NULL ) ;
	if (document == NULL) {
		printf("Failed to open file \n");
		return 1 ;
	}

	num_pages = poppler_document_get_n_pages( document ) ;
	printf("%d pages\n", num_pages) ;

	// Metadata
	
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
	
	// Contenu
/*
	for (i=0; i<num_pages; i++) {
		page = poppler_document_get_page( document, i ) ;
		text = poppler_page_get_text( page ) ;

		printf( "%s\n", text ) ;

	}
*/

	// images ? TODO

	
	// poppler_document_free(document) ; FIXME

	return 0 ;
}
