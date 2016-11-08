#pragma strict

private var player_stats : PlayerStats;
var GrenadeCasing : Rigidbody;
var EjectSpeed : int = 15;

function Start () {
    player_stats = GameObject.Find("PlayerStats").GetComponent(PlayerStats);
}

function Update () {
    if(player_stats.Grenades >= 1)
        if(Input.GetKeyDown("g")){
            var Grenade : Rigidbody;
            Grenade = Instantiate(GrenadeCasing, transform.position, transform.rotation);
            Grenade.velocity = transform.TransformDirection(Vector3.forward * EjectSpeed);
            player_stats.Grenades -= 1;
        }


}