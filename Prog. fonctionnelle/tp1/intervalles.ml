type inter = float*float;;

let inf (a,b) = a;;
let sup (a,b) = b;;

let min a b = if a<b then a else b;;
let max a b = if a<b then b else a;;

let vide (a,b) = if b>=a then false else true;;

(*       version sans prendre en compte les intervalles vides

let intersec i1 i2 = if not (vide i1) then
			if not (vide i2) then
			(max (inf i1) (inf i2), min (sup i1) (sup i2)) else i2 else i1;;

let ppic2i i1 i2 = if vide (intersec i1 i2) then intersec i1 i2 else (min (inf i1) (inf i2), max (sup i1) (sup i2));;


let contigu2 i1 i2 = if inf (intersec i1 i2) = sup (intersec i1 i2) then true else false;;
let contigu3 i1 i2 i3 = if contigu2 i1 i2 then 
                                            contigu2 (ppic2i i1 i2) i3
			                  else 
                        if contigu2 i1 i3 then
                                            contigu2 (ppic2i i1 i3) i2
                                          else false;;

*)

let normalize (a,b) = if b>a then (a,b) else (b,a);;

let intersec i1 i2 = (max (inf (normalize i1)) (inf (normalize i2)), min (sup (normalize i1)) (sup (normalize i2)));;

let ppic2i i1 i2 = if vide (intersec i1 i2) then intersec i1 i2 else (min (inf (normalize i1)) (inf (normalize i2)), max (sup (normalize i1)) (sup (normalize i2)));;


let contigu2 i1 i2 = if inf (intersec i1 i2) = sup (intersec i1 i2) then true else false;;
let contigu3 i1 i2 i3 = if contigu2 i1 i2 then 
                                            contigu2 (ppic2i i1 i2) i3
			                  else 
                        if contigu2 i1 i3 then
                                            contigu2 (ppic2i i1 i3) i2
                                          else false;;
