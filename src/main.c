#include <stdlib.h>
#include <stdio.h>

typedef struct s_node {
	char letter ;
	struct s_node* alternative ;
	struct s_node* next ;
} node_t ;

node_t* tree_new() ;
void tree_free( node_t* ) ;
node_t* tree_insert( node_t*, char* ) ;
int tree_search( node_t*, char* ) ;

node_t* tree_new() {
	return NULL ;
}

void tree_free( node_t* arbre ) {
	if ( arbre != NULL ) {
		tree_free( arbre->next ) ;
		tree_free( arbre->alternative ) ;
		free( arbre ) ;
	}
}

node_t* tree_insert( node_t* arbre, char* mot ) {
	if ( arbre == NULL ) {
		node_t* tmp = malloc( sizeof( node_t ) ) ;
		tmp->letter = mot[0] ;
		tmp->alternative = NULL ;
		tmp->next = NULL ;
		if ( mot[0] != '\0' )
			tmp->next = tree_insert( NULL, mot+1 ) ;
		return tmp ;
	} else {
		if ( arbre->letter == mot[0] ) { 
			if (mot[0] != '\0' )
				arbre->next = tree_insert( arbre->next, mot+1 ) ;
		} else 
			arbre->alternative = tree_insert( arbre->alternative, mot ) ;
		return arbre ;
	}
}

int tree_search( node_t* arbre, char* mot ) {
	if ( arbre == NULL )
		return 0 ;
	if ( arbre->letter == mot[0] ) {
		if ( mot[0] == '\0' )
			return 1 ;
		else
			return tree_search( arbre->next, mot+1 ) ;
	} else {
			return tree_search( arbre->alternative, mot ) ;
	}
}

int main( int argc, char** argv, char** envv ) {

	node_t* arbre ;
	char mot1[250]="coucou" ;
	char mot2[250]="chien" ;
	char mot3[250]="lapin" ;
	char mot4[250]="chienne" ;

	arbre = tree_new() ;
	arbre = tree_insert( arbre, mot1 ) ;
	arbre = tree_insert( arbre, mot2 ) ;
	arbre = tree_insert( arbre, mot3 ) ;
	arbre = tree_insert( arbre, mot4 ) ;

	printf( "coucou : %d\n", tree_search( arbre, "coucou" ) ) ;
	printf( "chienne : %d\n", tree_search( arbre, "chienne" ) ) ;
	printf( "chienn : %d\n", tree_search( arbre, "chienn" ) ) ;
	printf( "chienen : %d\n", tree_search( arbre, "chienen" ) ) ;


	
	tree_free( arbre ) ;
	return 0 ;
}
