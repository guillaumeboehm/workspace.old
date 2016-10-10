#pragma strict

var Health : int = 100;

function OnCollisionEnter(col : Collision){
    if(col.gameObject.tag == 'Bullet')
        Health -= 10;
}

function Update () {
    if(Health <= 0){
        GetComponent.<Animator>().Play("back_fall");
        gameObject.GetComponent(ZombieIA).enabled = false;
        gameObject.GetComponent(CharacterController).enabled = false;
        Dead();
    }
}

function Dead(){
    yield WaitForSeconds(120);
    Destroy(gameObject);
}