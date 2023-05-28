#ifndef DOCUMENT_H
#define DOCUMENT_H

#include "dict.h"

typedef enum {
	FILETYPE_PDF = 0,
	FILETYPE_EMAIL,
	FILETYPE_IMAGE
} filetype_t ;

typedef enum {
	LANG_FR = 0,
	LANG_EN
} lang_t ;


typedef struct {

								// hash SHA256 via implem openssl
	filetype_t type ;			// Document type
	lang_t	language ;			// Language
	time_t	timestamp ;			// Timestamp
	char* uri ;					// uri
	dict_t* keywords ;			// Keywords
	dict_t* candidates ;		// Possible keywords

} document_t ;

document_t *document_new( filetype_t filetype, 
		char* uri, lang_t lang, char** keywords ) ;
void document_free( document_t* ) ;

#endif
