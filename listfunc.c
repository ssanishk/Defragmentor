#include "global.h"
#include "freelist.h"
#include <stdio.h>
#include <stdlib.h>

void create_list ()
{
	int seq_no, key ;
	struct list* ptr ;

	ptr = (struct list*) malloc (sizeof(struct list)) ;
	ptr->head = free_top ;
	ptr->no_ele = 1 ;
	ptr->next = NULL ;


	if (list_start == NULL)
	{
		list_start = ptr ;
		seq_no = 1 ;
	}
	else
	{
		struct list* last ;
		last = list_start ;
		seq_no = 1 ;

		while (last->next != NULL)
		{
			last = last->next ;
			seq_no++ ;
		}
		last->next = ptr ;
		seq_no++ ;
	}

	printf ("The sequence number of the newly created list : %d\n" , seq_no) ;
	printf ("Enter key value to be inserted in the newly created list %d : " , seq_no) ;
	scanf ("%d" , &key) ;


	pop_free_list() ;
	//printf ("Free top = %d\n" , free_top) ;
	ram[ptr->head] = key ;
	ram[ptr->head + NEXT] = -1 ;
	ram[ptr->head + PREV] = -1 ;

	ram_used++ ;
	ram_free = ram_size - ram_used ;
	no_lists++ ;
}


void insert_ele (int listno, int key)
{
	struct list* ptr = list_start ;
	int seq_no = 1 , pos, key_index, prev_index ;

	key_index = free_top ;
	pop_free_list () ;
	ram[key_index] = key ;

	while (seq_no < listno)
	{
		ptr = ptr->next ;
		seq_no++ ;
	}

	prev_index = -1 ;
	pos = ptr->head ;

	while(key > ram[pos] && pos != -1)
	{
		prev_index = pos ;
		pos = ram[pos + NEXT] ;
	}

	if (pos != -1)
	{
		ram[key_index + NEXT] = pos ;
		ram[pos + PREV] = key_index ;

		if (prev_index == -1)
		{
			ptr->head = key_index ;
			ram[key_index + PREV] = -1 ;
		}
		else
		{
			ram[prev_index + NEXT] = key_index ;
			ram[key_index + PREV] = prev_index ;
		}
	}
	else if (pos == -1 && prev_index != -1)
	{
		ram[prev_index + NEXT] = key_index ;
		ram[key_index + PREV] = prev_index ;
		ram[key_index + NEXT] = -1 ;
	}
	else
	{
		ptr->head = key_index ;
		ram[key_index + NEXT] = -1 ;
		ram[key_index + PREV] = -1 ;
	}

	ptr->no_ele++ ;
	ram_used++ ;
	ram_free = ram_size - ram_used ;
}

void delete_ele (int listno, int key)
{
	struct list* ptr = list_start ;
	int seq_no = 1 , pos, prev_index, push_index, del_index ;

	while (seq_no < listno)
	{
		ptr = ptr->next ;
		seq_no++ ;
	}

	prev_index = -1 ;
	pos = ptr->head ;

	while(ram[pos] != key && pos != -1)
	{
		prev_index = pos ;
		pos = ram[pos + NEXT] ;
	}

	if (pos != -1)
	{
		push_index = pos ;
		ram[pos] = -1 ;


		if (pos == ptr->head)
		{
			del_index = pos ;
			if (ram[pos + NEXT] == -1)
				ptr->head = - 1 ;
			else
			{
				pos = ram[pos + NEXT] ;
				ptr->head = pos ;
				ram[pos + PREV] = -1 ;
			}
			ram[del_index + NEXT] = -1 ;
		}
		else
		{
			ram[prev_index + NEXT] = ram[pos + NEXT] ;
			ram[pos + PREV] = -1 ;

			if(ram[pos + NEXT] != -1)
			{
				del_index = pos ;
				pos = ram[pos + NEXT] ;
				ram[pos + PREV] = prev_index ;
				ram[del_index + NEXT] = -1 ;
			}

		}

		push_free_list(push_index) ;
		ptr->no_ele-- ;
		ram_used-- ;
		ram_free = ram_size - ram_used ;

		printf ("Success\n") ;
	}
	else if (pos == -1 && prev_index != -1)
		printf("Element is not there\n") ;
	else
		printf("The list is empty\n") ;
}

void no_ele_list (int listno)
{
	struct list *ptr ;
	ptr = list_start ;
	int seq_no = 1 ;

	while (seq_no < listno)
	{
		ptr = ptr->next ;
		seq_no++ ;
	}

	printf ("The number of elements in list %d = %d\n" , listno, ptr->no_ele) ;
}

void display_list(struct list *ptr)
{
	int index ;

	index = ptr->head ;
	while (index != -1)
	{
		printf ("%d \t ", ram[index]) ;

		if (ram[index+NEXT] == -1)
			printf("NULL \t ") ;
		else
			printf("%d \t " , ram[index+NEXT]) ;


		if (ram[index+PREV] == -1)
			printf("NULL") ;
		else
			printf("%d" , ram[index+PREV]) ;

		printf("\n") ;
		index = ram[index + NEXT] ;
	}
}

void display_all_lists ()
{
	struct list *ptr = list_start ;
	int count = 1 ;

	while (ptr != NULL)
	{
		printf("Elements of list %d are - \n" , count) ;
		printf ("Key \t Next \t Prev\n") ;

		if (ptr->no_ele != 0)
			display_list(ptr) ;
		else
			printf("NULL \t NULL \t NULL\n") ;
		ptr = ptr->next ;
		printf("\n") ;
		count++ ;
	}
}

void display_free_list ()
{

	printf ("Elements of free list are : \n") ;
	if (free_top == -1)
		printf("[NULL]") ;
	else
	{
		int trav ;
		trav = free_top ;

		printf("[") ;
		while (ram[trav + NEXT] != -1)
		{
			printf("%d, " , trav) ;
			trav = ram[trav + NEXT] ;
		}

		printf("%d]" , trav) ;
	}

	printf("\n") ;
}

