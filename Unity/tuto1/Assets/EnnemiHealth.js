#pragma strict

var EnnemiHealth : int = 100;
var Damage : int = 10;

function OnCollisionEnter(col : Collision){
    if(col.gameObject.tag == 'Bullet')
        EnnemiHealth -= Damage;
}

function Update () {
    if(EnnemiHealth <= 0)
        Destroy(gameObject);
}