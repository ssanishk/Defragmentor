#include "global.h"

void pop_free_list ()
{
	free_top = ram[free_top + NEXT] ;
}

void push_free_list (int push_index)
{
	ram[push_index + NEXT] = free_top ;
	free_top = push_index ;
}
