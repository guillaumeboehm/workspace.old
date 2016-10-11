(*calcul de la longueur d'un segment AB*)

let abscisse(x, y) = x;;
let ordonnee(x, y) = y;;
let pythagore(a, b) = sqrt(a*.a +. b*.b);;
let base(ptA, ptB) = abscisse(ptB) -. abscisse(ptA);;
let hauteur(ptA, ptB) = ordonnee(ptB) -. ordonnee(ptA);;

let longueur(ptA, ptB) =
	let ptM = (abscisse(ptB), ordonnee(ptA)) in
		pythagore(base(ptA, ptM), hauteur(ptB, ptM));;

print_string("entrer le x et le y des deux points :\n");;
print_float(longueur( (read_float(), read_float()), (read_float(), read_float()) ));;