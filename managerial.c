#include "global.h"
#include <stdio.h>
#include <stdlib.h>

int* create_free_list (int ram_size)
{
	int i ;
	int *ptr = (int*) malloc(ram_size * 3 * sizeof(int)) ;

	for (i = 0 ; i < ram_size*3 - 1 ; i++)
		ptr[i] = -1 ;

	ptr[1] = 3 ;
	ptr[ram_size*3 - 2] = -1 ;

	for (i = 3 ; i <= (ram_size-2)*3 ; i += 3)
		ptr[i+1] = i + 3 ;

	return(ptr) ;
}

void display_ram (int *ptr)
{
	int i ;

	printf("Ram Index - \n") ;
	for (i = 0 ; i < ram_size*3 - 1 ; i++)
	{
		printf ("%d\t" , i) ;
		if (i % 3 == 2)
			printf("||\t") ;
	}

	printf ("%d\n" , i) ;

	printf("Ram content - \n") ;
	for (i = 0 ; i < ram_size*3 - 1 ; i++)
	{
		printf ("%d\t" , ptr[i]) ;
		if (i % 3 == 2)
			printf("||\t") ;
	}

	printf ("%d\n" , ptr[i]) ;
}

void initialise ()
{
	//printf ("Enter the total number of nodes the RAM is capable of holding : ") ;
	//scanf ("%d" , &ram_size) ;
	//printf("\n") ;

	ram_size = 500 ;
	ram = create_free_list (ram_size) ;
	//display_ram (ram) ;
	free_top = 0 ;
	ram_used = 0 ;
	ram_free = ram_size ;
	no_lists = 0 ;
	list_start = NULL ;
}

void free_all ()
{
	free(ram) ;

	struct list* ptr,  *delptr ;
	ptr = list_start ;

	while (ptr->next != NULL)
	{
		delptr = ptr ;
		ptr = ptr-> next ;
		free(delptr) ;
	}
}
