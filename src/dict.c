#include <stdlib.h>
#include <stdio.h>
#include "dict.h"

void dict_display_rec( dict_t*, int, gunichar*, size_t  ) ;

dict_t* dict_new() {
	return NULL ;
}

dict_t* dict_build_from_file( const gchar* filename ) {
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

	char** word = words ;
	while ( **word != '\0' ) {
		gunichar* word_unichar = g_utf8_to_ucs4 ( *word, -1, NULL, NULL, NULL ) ;
        dico = dict_insert( dico, word_unichar ) ;
		g_free( word_unichar ) ;
		++word ;
    } 
    
    g_strfreev(words);

	return dico ;
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
		if ( tmp == NULL ) {
			fprintf(stderr, "malloc error in dict_insert \n") ;
			return arbre ;
		}
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

dict_t* dict_insert_char( dict_t* arbre, const char* mot ) {
	gunichar *mot_uni ;
	dict_t* tmp ;
	mot_uni = g_utf8_to_ucs4 ( mot, -1, NULL, NULL, NULL ) ;
	tmp = dict_insert( arbre, mot_uni ) ;
	g_free( mot_uni ) ;
	return tmp ;
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

int dict_search_char( dict_t* arbre, const char* mot ) {
	gunichar *mot_uni ;
	int tmp ;
	mot_uni = g_utf8_to_ucs4 ( mot, -1, NULL, NULL, NULL ) ;
	tmp = dict_search( arbre, mot_uni ) ;
	g_free( mot_uni ) ;
	return tmp ;
}

void dict_display( dict_t* dico ) {
	gunichar tableau[200] ;
	dict_display_rec( dico, 0, tableau, 200 ) ;
}


void dict_display_rec( dict_t* dico, 
						int position,
						gunichar* chaine,
						size_t size ) {
	if ( dico == NULL )
		return ;

	if ( dico->letter == U'\0' ) {
		chaine[position] = U'\0' ;
		gchar* mot_final = g_ucs4_to_utf8( chaine, -1, NULL, NULL, NULL ) ;
		printf("%s\n", mot_final );
		g_free(mot_final) ;
	} else {
		chaine[position] = dico->letter ;
		dict_display_rec( dico->next, position+1, chaine, size ) ; 
	}

	if ( dico->alt != NULL ) 
		dict_display_rec( dico->alt, position, chaine, size ) ;
}


int dict_count( dict_t* dico ) {
	int count_next ;
	int count_alt ;
	if ( dico == NULL ) {
		return 0 ;
	}

	count_next = dict_count( dico->next ) ;
	count_alt = dict_count( dico->alt ) ;
	
	if ( dico->letter == U'\0' )
		count_next += 1 ;

	return count_alt + count_next ;

}
	
