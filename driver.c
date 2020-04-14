#include <stdio.h>
#include <stdlib.h>
#include "global.h"
#include "freelist.h"
#include "managerial.h" 
#include "listfunc.h"
#include "defrag.h"

int main ()
{
	int input, reprompt = 0 ;

	initialise () ;

	//printf ("\nSize of the ram = %d nodes\n", ram_size) ;
	//printf ("Used space in ram = %d nodes\n", ram_used) ;
	//printf ("Free space in ram = %d nodes\n", ram_free) ;
	printf("\n") ;
	printf ("Select an option : \n"
			"1. Create a new list\n"
			"2. Insert a new element in a given list in sorted order\n"
			"3. Delete an element from the given list\n"
			"4. Count total elements excluding free list\n"
			"5. Count total elements of a list\n"
			"6. Display all lists\n"
			"7. Display free list\n"
			"8. Perform defragmentation\n"
			"9. Press 0 to exit\n") ;
	scanf ("%d" , &input) ;

	while (input != 0)
	{
		switch (input)
		{
			case 0 :
			{
				free_all () ;
				exit(0) ;
			}

			case 1 :
			{
				//printf ("Case 1\n") ;

				if (free_top != -1)
				{
					create_list() ;
					printf("Success\n") ;
				}
				else
					printf("Memory not available\n") ;


				reprompt = 0 ;
				break ;
			}

			case 2 :
			{
				//printf ("Case 2\n") ;

				int listno, key ;

				if (free_top != -1 && list_start != NULL)
				{
					do
					{
						printf ("Enter the number of the list you want to insert in : ") ;
						scanf ("%d" , &listno) ;

						if (listno > no_lists)
							printf ("Enter list number less than %d\n" , no_lists) ;
					} while (listno > no_lists) ;

					printf ("Enter the key value to be inserted : ") ;
					scanf ("%d" , &key) ;

				insert_ele (listno, key) ;
				printf("Success\n") ;
				}
				else
				{
					if (free_top == -1)
						printf("Memory not available\n") ;
					else if (list_start == NULL)
						printf("No list has been created yet\n") ;
				}

				reprompt = 0 ;
				break ;
			}

			case 3 :
			{
				//printf ("Case 3\n") ;

				int listno, key ;

				do
				{
					printf ("Enter the number of the list you want to delete from : ") ;
					scanf ("%d" , &listno) ;

					if (listno > no_lists)
						printf ("Enter list number less than %d\n" , no_lists) ;
				} while (listno > no_lists) ;

				printf ("Enter the key value to be deleted : ") ;
				scanf ("%d" , &key) ;

				delete_ele (listno, key) ;

				reprompt = 0 ;
				break ;
			}

			case 4 :
			{
				printf ("Total number of nodes in all lists : %d\n" , ram_used) ;

				reprompt = 0 ;
				break ;
			}

			case 5 :
			{
				int listno ;

				do
				{
					printf ("Enter the list number : ") ;
					scanf ("%d" , &listno) ;

					if (listno > no_lists)
						printf ("Enter list number less than %d\n" , no_lists) ;
				} while (listno > no_lists) ;

				no_ele_list (listno) ;

				reprompt = 0 ;
				break ;
			}

			case 6 :
			{
				display_all_lists () ;

				reprompt = 0 ;
				break ;
			}

			case 7 :
			{
				display_free_list () ;

				reprompt = 0 ;
				break ;
			}

			case 8 :
			{

				if (free_top == -1)
					printf ("No free space to defrag\n") ;
				else
				{
					defrag () ;
					printf("Success!\n") ;
				}

				reprompt = 0 ;
				break ;
			}

			default :
			{
				reprompt = 1 ;
				printf ("Incorrect input\n") ;
			}
		}


		/*
		if (reprompt != 1)
		{
			printf ("\n") ;
			display_ram (ram) ;
		}
		*/

		//printf ("\nSize of the ram = %d nodes\n", ram_size) ;
		//printf ("Used space in ram = %d nodes\n", ram_used) ;
		//printf ("Free space in ram = %d nodes\n", ram_free) ;
		printf("\n") ;
		printf ("Select an option : \n"
				"1. Create a new list\n"
				"2. Insert a new element in a given list in sorted order\n"
				"3. Delete an element from the given list\n"
				"4. Count total elements excluding free list\n"
				"5. Count total elements of a list\n"
				"6. Display all lists\n"
				"7. Display free list\n"
				"8. Perform defragmentation\n"
				"9. Press 0 to exit\n") ;
		scanf ("%d" , &input) ;
	}

	return 0 ;
}
