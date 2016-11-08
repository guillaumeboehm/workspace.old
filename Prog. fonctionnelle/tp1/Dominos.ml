type domino = int*int;;

let comp2 (a,b) (c,d) = a=c || a=d || b=c || b=d;;

let create2 (a,b) (c,d) = if a=c then (b,d) else
			  if a=d then (b,c) else
			  if b=c then (a,d) else
			  if b=d then (a,c) else (7,7);;

let comp3 (a,b) (c,d) (e,f) = if not (create2 (create2 (a,b) (c,d)) (e,f) = (7,7)) then true else
			      if not (create2 (create2 (a,b) (e,f)) (c,d) = (7,7)) then true else false;;
