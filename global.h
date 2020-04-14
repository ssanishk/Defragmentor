#include "listdata.h"

#define NEXT 1
#define PREV 2

int ram_size, free_top, ram_used, ram_free, no_lists ;
int *ram ;
struct list *list_start ;
