#include "suite.h"

#ifndef SSUITE_H
#define SSUITE_H

typedef struct { suite *ms;
				 int prem;
				 int ch[LG_MAX];
} ssuite;

void ss_print(ssuite u);

suite ss_ss2s(ssuite su);

ssuite ss_insert(ssuite su, int ind_of_u);

ssuite ss_cp_s_into_ss(suite *u);

ssuite ss_ss_croissante(suite *u);

#endif //SSUITE_H1