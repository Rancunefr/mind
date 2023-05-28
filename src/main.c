#include <stdio.h>
#include <locale.h>
#include <unistd.h>

#include "dict.h"
#include "document.h"
#include "pdf.h"


typedef enum {
	module_unknown ,
	doc ,
	keyword,
	language,
	disabled,
	type,
	local,
	remote
} module_t ;

typedef enum {
	action_unknown,
	add,
	del,
	replace,
	search,
	retrieve,
	update,
	disable,
	show,
	list,
	push,
	pull
} action_t ;

#define TEST_VALUE(Z,Y,X) (strncmp(Y,#X,strlen(Y))==0)?X:Z
#define STRINGIFY(z) #z

dict_t* dicts[NB_LANG] = { NULL } ;

dict_t*  k_keywords = NULL ;
dict_t*  K_keywords = NULL ;
int		 l_lang[NB_LANG] = { -1 }  ;	// -1 unknown, 0 disabled, 1 enabled
int		 t_type[NB_LANG] = { -1 }  ;	// -1 unknown, 0 disabled, 1 enabled

int main( int argc, char** argv, char** envv ) {

	module_t module = module_unknown ;
	action_t action = action_unknown ;

	if ( argc > 1 ) {
		module = TEST_VALUE(module, argv[1], doc) ;
		module = TEST_VALUE(module, argv[1], keyword) ;
		module = TEST_VALUE(module, argv[1], language) ;
		module = TEST_VALUE(module, argv[1], disabled) ;
		module = TEST_VALUE(module, argv[1], type) ;
		module = TEST_VALUE(module, argv[1], local) ;
		module = TEST_VALUE(module, argv[1], remote) ;
	} else {
		fprintf( stderr, "Usage: %s <module> <action> ... \n", argv[0] ) ;
		return 1 ;
	}

	if ( argc > 2 ) {
		action = TEST_VALUE(action, argv[2], add) ;
		action = TEST_VALUE(action, argv[2], del) ;
		action = TEST_VALUE(action, argv[2], replace) ;
		action = TEST_VALUE(action, argv[2], search) ;
		action = TEST_VALUE(action, argv[2], retrieve) ;
		action = TEST_VALUE(action, argv[2], update) ;
		action = TEST_VALUE(action, argv[2], disable) ;
		action = TEST_VALUE(action, argv[2], show) ;
		action = TEST_VALUE(action, argv[2], list) ;
		action = TEST_VALUE(action, argv[2], push) ;
		action = TEST_VALUE(action, argv[2], pull) ;
	} else {
		action = list ;
	}

	if ( module == module_unknown ) {
		fprintf(stderr, "Module %s is unknown \n", argv[1] ) ;
		fprintf(stderr, "\tValid values are: doc, keyword, language, disabled, type, local, remote\n") ;
		return 1 ;
	}

	if ( action == action_unknown ) {
		fprintf(stderr, "Action %s is unknown \n", argv[2] ) ;
		fprintf(stderr, "\tValid values are : add,del,replace,search,retrieve,update,disable,show,list,push,pull\n");
		return 1 ;
	}

	if ( argc > 3 ) {
		char opt ;
		gunichar* arg ;
		
		optind = 3 ;
		while ( (opt=getopt(argc, argv,"k:K:l:L:t:T:")) != -1 ) {
	
			printf("%c - %s\n", opt, optarg ) ;
			switch(opt) {
				case 'k':		// enable keyword
						arg = g_utf8_to_ucs4 ( optarg, -1, NULL, NULL, NULL ) ;
						dict_insert( k_keywords, arg ) ;
						g_free( arg ) ;
						break ;
				case 'K':		// disable keyword
						arg = g_utf8_to_ucs4 ( optarg, -1, NULL, NULL, NULL ) ;
						dict_insert( K_keywords, arg ) ;
						g_free( arg ) ;
						break ;
				case 'l':		// enable language
					break ;
				case 'L':		// disable language
					break ;
				case 't':		// enable doctype
					break ;
				case 'T':		// disable doctype
					break ;
				default:
					break ;
			}

		}
	}



/*
	setlocale(LC_ALL, "") ;
	document_t *doc ;

	doc = document_new( FILETYPE_PDF, argv[1], LANG_EN, NULL ) ;

	dicts[LANG_EN] = dict_build_from_file( "./dict.en" ) ;
	dicts[LANG_FR] = dict_build_from_file( "./dict.fr" ) ;

	printf( "%d \n", dict_count( dicts[LANG_FR]) ) ;
	printf( "%d \n", dict_count( dicts[LANG_EN]) ) ;

	load_pdf( doc ) ;

	dict_free( dicts[LANG_EN] ) ;
	dict_free( dicts[LANG_FR] ) ;

	document_free( doc) ;
*/
	return 0 ;
}
