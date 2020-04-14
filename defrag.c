#include <stdio.h>
#include <stdlib.h>
#include "global.h"

int first_used_from_right ()
{
	int fufr = (ram_size - 1)*3 ;

	while (ram[fufr] == -1)
		fufr -= 3 ;

	return fufr ;
}

struct list* findlist (int fufr_index)
{
	struct list *ptr = list_start ;

	while (ptr->head != fufr_index)
		ptr = ptr->next ;

	return ptr ;
}

void defrag ()
{
	int ram_index, fufr_index, prev_index, next_index ;
	int swap_key, swap_next, swap_prev ;

	ram_index = 0 ;

	while (ram_index <= (ram_used-1)*3 )
	{
		//printf("\nRam index = %d\n", ram_index) ;
		if (ram[ram_index] == -1)
		{
			fufr_index = first_used_from_right () ;

			swap_key = ram[ram_index] ;
			swap_next = ram[ram_index + NEXT] ;
			swap_prev = ram[ram_index + PREV] ;

			prev_index = ram[fufr_index + PREV] ;
			next_index = ram[fufr_index + NEXT] ;

			if (prev_index != -1)
				ram[prev_index + NEXT] = ram_index ;
			else
			{
				struct list* listhead ;
				listhead = findlist(fufr_index) ;

				listhead->head = ram_index ;
			}

			if (next_index != -1)
				ram[next_index + PREV] = ram_index ;

			ram[ram_index] = ram[fufr_index] ;
			ram[ram_index + NEXT] = ram[fufr_index + NEXT] ;
			ram[ram_index + PREV] = ram[fufr_index + PREV] ;

			ram[fufr_index] = swap_key ;
			ram[fufr_index + NEXT] = swap_next ;
			ram[fufr_index + PREV] = swap_prev ;
		}

		ram_index += 3 ;

		/*
		printf("Check it -") ;
		int dummy ;
		scanf("%d" , &dummy) ;
		display_ram (ram) ;
		printf("\n") ;
		*/
	}

	ram_index = ram_used*3 ;
	while (ram_index < ram_size*3)
	{
		ram[ram_index] = -1 ;
		ram_index++ ;
	}

	ram_index = ram_used*3 ;
	while (ram_index <= (ram_size-2)*3)
	{
		ram[ram_index + NEXT] = ram_index + 3 ;
		ram_index += 3 ;
	}

	free_top = ram_used*3 ;
}
