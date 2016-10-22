#ifndef NAT0_H
#define NAT0_H

#include "bool.h"
#include <stdio.h>

#define _Nat_ struct sn *

struct sn {
    char f;       // symbole d'opération 0 ou s
    _Nat_ p; // prédécesseur
                         };

typedef _Nat_ Nat;

Nat O();
Nat s(Nat n);
Nat add(Nat n, Nat m);
Nat mult(Nat n, Nat m);

Bool zero(Nat n);
Bool estsucc(Nat n);

void printn(Nat n);
Nat u2nat(unsigned u);
unsigned nat2u(Nat n);

#endif //NAT0_H