#pragma strict

var bulletCasing : Rigidbody;
var ejectSpeed : int = 100;
var fireRate : float = 0.5; //cadence de tir
private var nextFire : float = 0.0; //temps entre deux tirs
private var fullAuto = false; //full auto ou coup par coup

var maxClip : int = 30; //nombre de balles max dans le chargeur
var clip : int = maxClip; //chargeur
var ammoStock : int = maxClip * 10; //stock de balles
var minAmmoStock : int = 0;

function Update () {

    /*si la touche de tir est appuyee*/
    if(Input.GetButton("Fire1") && Time.time > nextFire){
        if(clip >= 1){
            nextFire = Time.time + fireRate; //temps entre deux tirs

            var bullet : Rigidbody;
            bullet = Instantiate(bulletCasing, transform.position, transform.rotation);
            bullet.velocity = transform.TransformDirection(Vector3.left * ejectSpeed); //vitesse de base de la balle

            clip--; //enleve une balle du chargeur
        }
    }
    /***************************/

    /*changement de mode de tir*/
    if(Input.GetKeyDown("v")){
        fullAuto = !fullAuto;

        if(fullAuto)
            fireRate = 0.10;
        else
            fireRate = 0.5;
    }
    /************************/

    /*recharger*/
    if(Input.GetKeyDown("r")){
        if(ammoStock >= minAmmoStock && ammoStock >= maxClip - clip){
            ammoStock -= maxClip - clip;
            clip = maxClip;
        }
        else{
            clip += ammoStock;
            ammoStock = minAmmoStock;
        }
    }

    if(clip > maxClip) //just in case XD
        clip = maxClip;
    if(ammoStock < minAmmoStock)
        ammoStock = minAmmoStock;
    /******************/
}

function OnGUI(){
    GUI.Box(Rect(10,10,150,30), clip+" : "+ammoStock);
}