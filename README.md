c-arraylist
===========

An arraylist (dynamic array) written in C.

# ArrayList #

## Synopsis ##

```

typedef struct{
    size_t data_size;
    size_t max_length;
    size_t length;
    void *array;
    int (* add)();
    int (* remove)();
    void* (* get)();
    int (* set)();    
    int (* free)();
} ArrayList
```

Any of the methods that return an integer will return one of the corresponding values:<br />
`ALSUCCESS`: the method was successful<br />
`RMNODATA`: a remove was called, but there was no data in the list<br />
`ALIDXOOR`: Index Out Of Range<br />
The `get` method will return a null pointer if the index is out of bounds.

## Constructors ##
Both of these functions require the size of data type to be stored and will return a pointer to the struct ArrayList that is malloc'd.

```
ArrayList *newArrayList( size_t data_size );
```
Returns a pointer to the malloc'd ArrayList struct using a default max size of 10 items.

```
ArrayList *newArrayListSized( size_t data_size, size_t initial_length );
```
If the size of an array is known, use the initial length argument to set the initial max length of the array. Returns a pointer to the malloc'd ArrayList struct.


## Methods ##
Assume that for each method there is already an allocated struct: 
```ArrayList *list = newArrayList( sizeof( int ) );```

### int add( ArrayList *list, void *data ); ###
```
// Example
int data = 10;
list->add( list, &data );
```
Adds (copies) the data pointed to by ```data``` to the next open space in the array.

### int remove( ArrayList *list, int index ); ###
```
// Example
list->remove( list, 10 );
```
Removes an item from the array at index `index`.

### void \*get( ArrayList *list, int index ); ###
```
// Example
int *data;
data = list->get( list, 2 );
printf( "%d", *data );
>>> 123
```
Returns a void pointer to the item in array index ```index```.

### set( ArrayList *list, int index, void *data ); ###
```
// Example
int data = 42;
list->set( list, 13, &data );
```
Copies the value at from  ```data``` to ```index```.

### free( ArrayList *list ); ###
```
// Example
list->free( list );
```
Destroys **all** memory allocated for the ArrayList `list`.

## Notes ##
1. ArrayLists are indexed starting at 0.
2. An index can be a negative number. For example, choosing an index of -1 will return the last item in the array.
