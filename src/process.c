#include "process.h"

gint g_unichar_strlen( gunichar* ) ;
gunichar* get_next_word( gunichar*, gunichar**) ;
void process_word( gunichar* ) ;


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
		return ;
	}

	// TODO: INDEXATION
	
	// printf("%s \n", g_ucs4_to_utf8( mot, -1, NULL, NULL, NULL ) );

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


