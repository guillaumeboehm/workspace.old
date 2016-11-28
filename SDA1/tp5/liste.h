#ifndef LISTE_H
#define LISTE_H

#include "bool.h"
#include <stdio.h>

typedef struct sldc {
	S e;	//element
	struct sldc *n; //next
	struct sldc *p; //previous
} *liste;



#endif //LISTE_H