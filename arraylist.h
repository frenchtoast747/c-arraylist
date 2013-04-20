#ifndef ARRAYLIST_H
#define ARRAYLIST_H

/* GLOBALS */
enum {  ALSUCCESS,
        RMNODATA,
        ALIDXOOR
};

typedef struct{
    size_t data_size;   /* the size of the data being stored */
    size_t max_length;  /* the current max length of the list */
    size_t length;      /* the current length of the list */
    void *array;
    int (*add)();
    int (*remove)();
    void *(*get)();
    int (*set)();
    void (*free)();
} ArrayList;

ArrayList *newArrayList( size_t data_size );
ArrayList *newArrayListSized( size_t data_size, size_t initial_length );
int ArrayList__getoffset( ArrayList *list, int index );
int ArrayList_add( ArrayList *list, void *data );
int ArrayList_remove( ArrayList *list, int index );
void ArrayList__realloc( ArrayList *list );
void *ArrayList_get( ArrayList *list, int index );
int ArrayList_set( ArrayList *list, int index, void *data );
void ArrayList_free( ArrayList *list );
char *ArrayList_toString( ArrayList *list );
    
#endif
