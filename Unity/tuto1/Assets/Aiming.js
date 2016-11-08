#pragma strict

var normalPos : Vector3;
var aimPos : Vector3;

function Start () {
    transform.localPosition = normalPos;
}

function Update () {
    if(Input.GetButton("Fire2"))
        transform.localPosition = aimPos;
    else
        transform.localPosition = normalPos;
}