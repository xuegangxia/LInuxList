#ifndef _TYPES_H_
#define _TYPES_H_

#include "list.h"

#define HASHLISTLENTGH  103

typedef struct{
	char name[100];         				
	char id[30];                                           
	struct list_head list;/*linux list head*/
}NODE;



#endif