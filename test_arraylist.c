#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "arraylist.h"

void printlist( ArrayList *list ){
    int *datap;
    for( int i=0; i<list->length; i++ ){
        datap = list->get( list, i );
        if( datap == NULL ){
            printf( "\nINDEX OUT OF BOUNDS!\n" );
            exit( 1 );
        }
        printf( "Index: %d, Value: %d\n", i, *datap );
    }
    printf( "\n" );
}

int main(){
    ArrayList *list = newArrayList( sizeof( int ) );
    
    int data = 5;
    for( int i=0; i<10000; i++ ){
        printf( "Adding: %d at index %d.\n", data, i );
        if( list->add( list, &data ) == ALIDXOOR ){
            printf( "Error: Index Out of Range" );
            exit( 1 );            
        }
        data += 5;
    }

    printf( "\n" );
    printlist( list );

    list->remove( list, 5 );
    list->remove( list, -1 );
    
    printlist( list );
    
    data = 10001;
    if( list->set( list, 5, &data ) == ALIDXOOR ){
        printf( "Error: Index Out of Range" );
        exit( 1 );
    }
    printlist( list );

    printf( "Length: %d\n", list->length );
    printf( "Max Length: %d\n", list->max_length );

    list->free( list );
    
    list = newArrayList( sizeof( char ) );
    char a[] = "a";
    char b[] = "b";
    char c[] = "c";
    
    for( int i=0; i<100000; i++ ){
        list->add( list, a );
        list->add( list, b );
        list->add( list, c );
    }

    printf( "\n" );
    printf( "Chars:\n" );
    write( STDOUT_FILENO, list->array, list->length );

    list->free( list );
}
