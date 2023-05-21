#ifndef DOCUMENT_H
#define DOCUMENT_H

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
	// filename
	// keywords
	// langue
	// type de document ( mails, pdf, docx, image )
	// timestamp
	// version ???

} document_metadata ;


#endif
