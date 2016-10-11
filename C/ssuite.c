#include "ssuite.h"

void ss_print(ssuite su){
	int i = su.prem;
	for(; i!=(-1); i=su.ch[i])
		printf("%d\t", su.ms->val[i]);
}

suite ss_ss2s(ssuite su){
	suite u = s_vide();
	int i = su.prem;
	for(; i!=(-1); i=su.ch[i])
		u.val[u.lg++] = su.ms->val[i];
	return u;
}

ssuite ss_insert(ssuite su, int ind_of_u){
	if(ind_of_u < su.prem){
		su.ch[ind_of_u] = su.prem;
		su.prem = ind_of_u;
	}
	else{
		int pos=su.prem;
		for(; su.ch[pos]<ind_of_u && su.ch[pos]!=(-1); pos=su.ch[pos]);
		if(su.ch[pos] > ind_of_u || su.ch[pos] == -1){
			su.ch[ind_of_u] = su.ch[pos];
			su.ch[pos] = ind_of_u;
		}
	}
}

ssuite ss_cp_s_ito_ss(suite *u){
	ssuite su;
	su.prem = 0;
	su.ms = u;
	int i = 0;
	for(; i<u->lg-1;;)
		su.ch[i] = ++i;
	su.ch[i] = -1;
	return su;
}

ssuite ss_cp_s_into_ss_pair(suite *u){
	ssuite su = ss_vide();
	su.ms = u;
	int i = 0;
	for(; i<u->lg-2;i+=2;)
		su.ch[i] = i+2;
	return su;
}

ssuite ss_ss_croissante(suite *u){
	
}