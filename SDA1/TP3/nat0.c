#include "nat0.h"

Nat O(){
	Nat ret = (Nat) malloc(sizeof(struct sn));
	ret->f = '0';
	ret->p = NULL;
	return ret;
}

Nat s(Nat n){
	Nat ret = (Nat) malloc(sizeof(struct sn));
	ret->f = 's';
	ret->p = n;
}

Nat add(Nat n, Nat m){
	return n->f == '0' ? m : s(add(n->p, m));
}

Nat mult(Nat n, Nat m){
	return n->f == '0' ? 0 : add(mult(n->p, m), m);
}

Bool zero(Nat n){
	return n->f == '0';
}

Bool estsucc(Nat n){
	return n->f == 's';
}

void hide_printn(Nat n){
	if(estsucc(n)){
		printf("s(");
		printn(n->p);
		printf(")");
	}
	else{
		printf("0");
	}
}

void printn(Nat n){
	hide_printn(n);
	printf("\n");
}

Nat u2nat(unsigned u){
	Nat ret = O();
	for(unsigned int i=0; i<u; ++i){
		ret = s(ret);
	}
	return ret;
}

unsigned nat2u(Nat n){
	unsigned int compt = 0;
	while(estsucc(n)){
		compt++;
		n = n->p;
	}
	return compt;
}