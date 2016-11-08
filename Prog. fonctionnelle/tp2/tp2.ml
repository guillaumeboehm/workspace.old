let rec puissance x n = if n > 0 then x*.(puissance x n-1) else 1.;;

let rec pgcd a b = if b = 0 then a else pgcd b (a mod b);;

let fib n = if n>1 then fib (n-1) + fib (n-2) else if n = 1 then 1 else 0;;
