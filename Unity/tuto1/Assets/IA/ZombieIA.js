#pragma strict

var Distance : float;
var Target : Transform;
var LookAtDistance : int = 20;
var ChaseRange : int = 10;
var AttackRange : float = 2.2;
var MoveSpeed : int = 3;
var Damping : int = 6;
var AttackRepeatTime : float = 1.0;
var Dammage : int = 20;

private var AttackTime : float;

var Controller : CharacterController;
var Gravity : float = 20;

private var MoveDirection : Vector3 = Vector3.zero;

function Start () {
    AttackTime = Time.time;
    FindTarget();
}

function Update () {
    Distance = Vector3.Distance(Target.position, transform.position);
    
    if(Distance < LookAtDistance)
        LookAt();
    
    if(Distance < AttackRange)
        Attack();
    else if(Distance < ChaseRange)
        Chase();
     
}

function LookAt(){
    var rotation = Quaternion.LookRotation(Target.position - transform.position);
    transform.rotation = Quaternion.Slerp(transform.rotation, rotation, Time.deltaTime * Damping);
}

function Chase(){
    GetComponent.<Animator>().Play("walk");

    MoveDirection = transform.forward;
    MoveDirection *= MoveSpeed;

    MoveDirection.y -= Gravity * Time.deltaTime;
    Controller.Move(MoveDirection * Time.deltaTime);
}

function Attack(){
    if(Time.time > AttackTime){
        GetComponent.<Animator>().Play("attack");

        Target.SendMessage("ApplyDammage", Dammage);

        AttackTime = Time.time + AttackRepeatTime;
    }
}

function ApplyDammage(){
    ChaseRange += 30;
    LookAtDistance += 40;
}

function FindTarget(){
    Target = GameObject.Find("PlayerStats").GetComponent(PlayerStats).transform;
}