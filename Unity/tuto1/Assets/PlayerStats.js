#pragma strict

var Grenades : int = 2; //nombre de grenades dispo

var MaxHealth : int = 100;
var Health : int = MaxHealth;

function ApplyDammage(Dammage : int){
    Health -= Dammage;

    if(Health <= 0)
        Dead();
}

function Dead(){
    Debug.Log("Player Died");
}