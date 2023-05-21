#include <stdlib.h>
#include "dict.h"

dict_t* dict_new() {
	return NULL ;
}

void dict_free( dict_t* arbre ) {
	if ( arbre != NULL ) {
		dict_free( arbre->next ) ;
		dict_free( arbre->alt ) ;
		free( arbre ) ;
	}
}

dict_t* dict_insert( dict_t* arbre, gunichar* mot ) {
	if ( arbre == NULL ) {
		dict_t* tmp = malloc( sizeof( dict_t ) ) ;
		tmp->letter = mot[0] ;
		tmp->alt = NULL ;
		tmp->next = NULL ;
		if ( mot[0] != '\0' )
			tmp->next = dict_insert( NULL, mot+1 ) ;
		return tmp ;
	} else {
		if ( arbre->letter == mot[0] ) { 
			if (mot[0] != '\0' )
				arbre->next = dict_insert( arbre->next, mot+1 ) ;
		} else 
			arbre->alt = dict_insert( arbre->alt, mot ) ;
		return arbre ;
	}
}

int dict_search( dict_t* arbre, gunichar* mot ) {
	if ( arbre == NULL )
		return 0 ;
	if ( arbre->letter == mot[0] ) {
		if ( mot[0] == U'\0' )
			return 1 ;
		else
			return dict_search( arbre->next, mot+1 ) ;
	} else {
			return dict_search( arbre->alt, mot ) ;
	}
}

dict_t* build_dict_from_file( const gchar* filename ) {
	dict_t* dico ;
	gchar* contents ;
	gsize length ;

	dico = dict_new() ;

	// Read the entire file into a string
    if (!g_file_get_contents(filename, &contents, &length, NULL)) {
        g_print("Failed to read file: %s\n", filename);
        return NULL ;
    }

    gchar** words = g_strsplit(contents, "\n", -1);
    g_free(contents);
    
    // Iterate over the words and print them
    for (gchar** word = words; *word; ++word) {
		gunichar* word_unichar = g_utf8_to_ucs4 ( *word, -1, NULL, NULL, NULL ) ;
        dico = dict_insert( dico, word_unichar ) ;
		g_free( word_unichar ) ;
    }
    
    g_strfreev(words);

	return dico ;
}

