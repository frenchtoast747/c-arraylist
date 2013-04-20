#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "arraylist.h"

/*-----------------------------------
  The Array List Data Structure
----------------------------------- */
/*
  To use the ArrayList, you must first specify the type of
  Array by specifying the size of the element. This is used
  to calculate the index in memory and allows for this list
  to be reused with multiple data types.
 */
ArrayList *newArrayList( size_t data_size ){
    return newArrayListSized( data_size, 10 );
}
ArrayList *newArrayListSized( size_t data_size, size_t initial_length ){
    ArrayList *list = malloc( sizeof( ArrayList ) );
    list->data_size = data_size;
    list->max_length = initial_length;
    list->length = 0;
    list->array = malloc( data_size * initial_length );
    list->add = ArrayList_add;
    list->remove = ArrayList_remove;
    list->get = ArrayList_get;
    list->set = ArrayList_set;
    list->free = ArrayList_free;
    return list;
}
int ArrayList__getoffset( ArrayList *list, int index ){
    /* returns the pointer offset integer based on the
       given index and the size of the data stored.
       This functions handles index out of bounds errors
       so be sure to use this function when handling
       indices on an array.

       returns -1 on an index out of bounds error
    */
    if( index < 0 ){
        // if the index is a negative number, allow
        // that to be index number of items from the
        // end of the array towards the beginning.
        // This here sets index the position from the
        // end and then shifts it to be zero indexed.
        index = list->length + index;
    }
    if( index > list->length ){
        return -1;
    }
    if( index > list->max_length - 1 ){
        return -1;
    }
    return index * list->data_size;
}
int ArrayList_add( ArrayList *list, void *data ){
    int offset;
    if( list->length < 1 ){
        offset = 0;
    }
    else{
        offset = ArrayList__getoffset( list, -1 );
    }
    // check to see if there is enough room in the array
    if( list->length + 1 > list->max_length ){
        ArrayList__realloc( list );
    }
    // copy the data from *data into the last free index of the array
    memcpy( list->array + offset, data, list->data_size );
    list->length++;
    return ALSUCCESS;
}
int ArrayList_remove( ArrayList *list, int index ){
    /*
      Removes the item at index from list

      Returns ALSUCCESS upon successful removal
              RMNODATA if a removal was requested upon an empty array
     */
    if( list->length < 1 ){
        return RMNODATA;
    }
    // if this is the last item in the array, just decrement the size
    if( index == list->length - 1 || index == -1 ){
        list->length--;
        return ALSUCCESS;
    }
    // number of bytes from the array pointer to the data to be removed
    int offset = ArrayList__getoffset( list, index );
    if( offset == -1 ) return ALIDXOOR;
    // pointer to where the next data lives
    int replacement = ArrayList__getoffset( list, index + 1 );
    if( replacement == -1 ) return ALIDXOOR;
    // number of bytes to end of array
    int remaining_data = (list->length * list->data_size) - replacement;
    memmove( list->array + offset, list->array + replacement, remaining_data );
    list->length--;
    return ALSUCCESS;
}
void *ArrayList_get( ArrayList *list, int index ){
   /*
      Returns a pointer to the data at index 'index' in the list
   */
    int offset = ArrayList__getoffset( list, index );
    if( offset == -1 ) return NULL;
   return list->array + offset;
}
int ArrayList_set( ArrayList *list, int index, void *data ){
    /*
      Copies the data pointed to by data into the index position
      in the array.

      Returns ALSUCCESS on success
              ALIDXOOR for an index out of range
     */
    int offset = ArrayList__getoffset( list, index );
    if( offset == -1 ) return ALIDXOOR;
    memcpy( list->array + offset, data, list->data_size );
    return ALSUCCESS;
}
void ArrayList__realloc( ArrayList *list ){
    list->array = realloc( list->array, list->data_size * list->max_length * 2 );
    if(!list->array){
        perror( "Could not reallocate memory for array size increase." );
        exit( EXIT_FAILURE );
    }
    list->max_length *= 2;
}
void ArrayList_free( ArrayList *list ){
    free( list->array );
    free( list );
    list = NULL;
}
