#ifndef PROCESS_H
#define PROCESS_H

#include <glib.h>
#include "document.h"

typedef enum {
	TXT_Content,
	TXT_Author,
	TXT_Subject,
	TXT_Title,
	TXT_Keyword,
	TXT_Metadata
} text_t ;

void process_text( gunichar* text, text_t type, document_t *doc ) ;

#endif
