#pragma strict

function Start () {
    yield WaitForSeconds(5);
    Destroy(gameObject);
}