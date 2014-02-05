#include<stdio.h>
#include<stdlib.h>
#include<string.h>


typedef struct array{
	 int *data; /*pointer to my data*/
	 int els; /*how many elements are in the array*/
	 int arraysize; /*how many elements the array can hold*/
	 int memsize; /*memory size of arraylist*/
	 int (*append)(struct array*, int val);
	 int (*print)(struct array*);
	 int (*set)(struct array*, int val, int index);
	 int (*insert)(struct array*, int val, int index);
	 int (*destroy)(struct array*);
	 int (*valueOf)(struct array*, int element);
	 int (*size)(struct array*);
	 int (*capacity)(struct array*);

} ArrayList;

/* BASIC API 

	ArrayList list = NULL;
	list = ArrayList_Init(n); // init a new list with capacity n
	stat = list->append(list,val) ; // add val to end of the list
	stat = list->print(list); // simple display of list contents
	stat = list->set(list,val, index) ;// put val into index
	stat = list->insert(list, vali, index); // insert val into index (increasing ArrayList size by one, and bumping all values over)
	stat = list->destroy(list) ;//free list memory
	val = list->valueOf(list,element) ;//return value of specified element
	size = list->size(list); // return the size of the list
	capacity = list->capacity(list); // return the number of elements currently allocated by list

	FUNCTION PROTOTYPES */

ArrayList * ArrayList_Init( int n );
int capacity(ArrayList *list);
int append( ArrayList *list, int val );
int print( ArrayList *list );
int set( ArrayList *list, int val, int index );
int insert(ArrayList *list, int val, int index);
int destroy( ArrayList *list );
int valueOf( ArrayList *list, int element );
int size(ArrayList *list);





ArrayList * ArrayList_Init( int n )
{
	 /* Dynamically allocates a new ArrayList structure with n elements */
	 /* Elements do not need to be initialized to any particular value */
	 /* (don't forget to assign function pointers!) */
	 /* Both the size and capacity of ArrayList at this point should be n */

	 /* return pointer to allocated space */
	 if(n>0){
		  ArrayList *list = malloc(sizeof(ArrayList));
		  list->data = malloc(sizeof(int)*n); 
		  list->els = n;
		  list->memsize = n*sizeof(int);
		  list->arraysize = n;
		  list->size = size;
		  list->capacity = capacity;
		  list->append = append;
		  list->print = print;
		  list->set = set;
		  list->insert = insert;
		  list->destroy = destroy;
		  list->valueOf = valueOf;
	 	return list;
	 }
	 else{
		  ArrayList *list = malloc(sizeof(ArrayList));
		  list->data = malloc(sizeof(int));
		  list->els = n;
		  list->memsize = sizeof(int);
		  list->arraysize = 1;
		  list->size = size;
		  list->capacity = capacity;
		  list->append = append;
		  list->print = print;
		  list->set = set;
		  list->insert = insert;
		  list->destroy = destroy;
		  list->valueOf = valueOf;
	 return list;

	 }
}

int append( ArrayList *list, int val )
{
	 /* increases size of list by one, and appends val to last element in
		 newly resized list */

	 /* return 0 if success */
	 /* return 1 if memory is not available from malloc */

	 if(list->els < list->arraysize){
		  list->data[list->els] = val;
		  list->els++;
		  return 0;
	 }
	 else{
				list->data = realloc(list->data, 2 * list->memsize);
				if(list->data == NULL){
					 return 1;
				}

				else{

					 list->data[list->els] = val;
					 list->els++;
					 list->memsize = 2 * list->memsize;
					 list->arraysize = 2 * list->arraysize;
					 return 0;
				}
		  }
	 }

int print( ArrayList *list )
{
	 /* prints the entire ArrayList to stdout */
	 /* Note - number of integers printed is the size of the list, not capacity */
	 /* Format should be simple: integers delimited by single spaces, ended by newline */

	 /* return 0 for success */
	 /* return 1 if trying to print an empty list (i.e., list initialized
		 to size 0 )*/
	 if(list->els == 0){
		  return 1;
	 }
	 else{
		  int i=0;
		  while(i<list->els){
				printf("%i ", list->data[i]);
				i++;
		  }
		  printf("\n");

		  return 0;
	 }
}

int set( ArrayList *list, int val, int index )
{
	 /* sets the value at index 'index' to 'val'. */

	 /* return 0 for success */
	 /* return 1 if index out-of bounds, i.e.,: index < 0 or index >= size */
	 if(index < 0 || index >= list->els){
		  return 1;
	 }
	 else{
		  list->data[index] = val;

		  return val;
	 }}

int insert(ArrayList *list, int val, int index)
{
	 /* insert val into index (increasing ArrayList size by one, and bumping all values over)*/
	 /* This function may or may not require increasing capacity / allocating
		 more memory */

	 /* return 0 for success */
	 /* return 1 if index out-of bounds, i.e.,: index < 0 or index >= size */
	 int i;
	 if(index < 0 || index >= list->els){
		  return 1;
	 }
	 else{
		  if(list->els < list->arraysize){
				for(i = list->els; i > index; i--){
					 list->data[i] = list->data[i-1];
				}
				list->els++;
				list->data[index] = val;
				return 0;
		  }
		  else{
				list->data = realloc(list->data, 2 * list->memsize);
				if(list->data == NULL){
					 return 1;
				}
				else{
					 list->arraysize = 2 * list->arraysize;
					 list->memsize = 2 * list->memsize;
					 for(i = list->els; i > index; i--){
						  list->data[i] = list->data[i-1];
					 }

					 list->data[index] = val;
					 list->els++;
					 return 0;
				}
		  }	 

	 }
}



int destroy( ArrayList *list )
{
	 /* frees ALL memory associated with list. This includes underlying data structure memory AND memory for ArrayList struct itself */

	 /* returns 0 for success */
	  free(list->data);
			 free(list);
	   return 0;
}

int valueOf( ArrayList *list, int element )
{
	 /* return the integer value at index 'element' */
	 return list->data[element];
}

int size(ArrayList *list)
{
	 /* returns the current size of the ArrayList */
	 return list->els;

}

int capacity(ArrayList *list)
{
	 /* return the number of elements currently allocated by list */
	 return list->arraysize;
}



/* TEST MAIN */
int main(void)
{
	 int n = 3;
	 int i;
	 int stat; // Error code
	 int size;
	 int val = 0;
	 int capacity;


	 // allocate list
	 ArrayList *list = NULL;
	 list = ArrayList_Init(n);
	 printf("ArrayList initialized to %d elements\n", n);
	 printf("Size of List = %d\n", list->size(list));
	 printf("Capacity of List = %d\n", list->capacity(list));

	 // Fill initial values

	 list->set(list, val++, 0);
	 list->set(list, val++, 1);
	 list->set(list, val++, 2);

	 // Print List
	 stat = list->print(list); // simple display of list contents
	 printf("Size of List = %d\n", list->size(list));
	 printf("Capacity of List = %d\n", list->capacity(list));

	 // Test append and auto-resize
	 stat = list->append(list,val++) ; // add val to end of the list
	 stat = list->print(list); // simple display of list contents
	 printf("Size of List = %d\n", list->size(list));
	 printf("Capacity of List = %d\n", list->capacity(list));

	 // Some more appends
	 stat = list->append(list,val++) ; // add val to end of the list
	 stat = list->append(list,val++) ; // add val to end of the list
	 stat = list->print(list); // simple display of list contents
	 printf("Size of List = %d\n", list->size(list));
	 printf("Capacity of List = %d\n", list->capacity(list));

	 // Test insert
	 stat = list->insert(list, val++, 1); // insert val into index (increasing ArrayList size by one, and bumping all values over)
	 stat = list->print(list); // simple display of list contents
	 printf("Size of List = %d\n", list->size(list));
	 printf("Capacity of List = %d\n", list->capacity(list));

	 // Test insert redux
	 stat = list->insert(list, val++, 4); // insert val into index (increasing ArrayList size by one, and bumping all values over)
	 stat = list->print(list); // simple display of list contents
	 printf("Size of List = %d\n", list->size(list));
	 printf("Capacity of List = %d\n", list->capacity(list));

	 // Test valueOf
	 stat = list->print(list); // simple display of list contents
	 printf("list[0] = %d\n", list->valueOf(list,0)) ;//return value of specified element
	 printf("list[1] = %d\n", list->valueOf(list,1)) ;//return value of specified element


	 // Test error handling
	 printf("insert error = %d\n", list->insert(list, val++, 1000));
	 printf("insert error = %d\n", list->insert(list, val++, -1000));
	 printf("set error = %d\n", list->set(list, val++, 1000));
	 printf("set error = %d\n", list->set(list, val++, -1000));
	 ArrayList *list2 = ArrayList_Init(0);
	 stat = list2->print(list2);
	 printf("bad print error = %d\n", stat);

	 // Test efficiency
	 // NOTE - grading script will kill your code if this takes > 3 seconds
	 val = 0;
	 printf("Efficiency test...\n");
	 for( i = 0; i < 10000000; i++ )
		  list2->append(list2, val++ );

	 // test destroy
	 stat = list->destroy(list); //free list memory
	 stat = list2->destroy(list2); //free list memory

	 return 0;
}



