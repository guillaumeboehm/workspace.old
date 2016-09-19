(*TP noté de Lambda-calcul*) 			(*Morgane RITTER*)

(*1.Questions préliminaires*)

(*1*)
let rec union l1 l2 = match l1 with
	[]->l2
	| t::r -> if List.mem t l2 then union r l2 else t::union r l2;; 

(*2*)						
let rec inter l1 l2 = match l1 with
	[]->[]
	| t::r -> if List.mem t l2 then t::inter r l2 else inter r l2;;

(*Fonction auxilliare*)	
let rec suppr l1 x = match l1 with 
	[]->[]
	| t::r -> if t=x then suppr r x  else t::(suppr r x);;

(*2.Lambda-terme*)

(*1*)
type terme =
	 Cst of string
	|Var of string
	|Abs of string * terme
	|App of terme * terme;;

(*2*)	
let terme1 = Abs("x",Var"x");;
let terme2 = App(terme1,Var "a");;
let terme3 = Abs("x",Abs("y",Var "y"));;
let terme4 = Abs("x",Abs("y",Abs("z",App(App(Var"x",Var"z"),App(Var "y",Var "z")))));;
let terme5 = Abs("x",App(Var"x",Var"x"));;
let terme6 = App(terme5, terme5);;

(*Terme supplementaire*)
let terme7 = Abs("x",Abs("y",App(Var "x", Var "y")));;
let terme8 = App(App(Abs("m",Abs("n",Abs("f",App(Var "n",App(Var "m", Var "f"))))),Abs("f",Abs("x",App(Var "f", Var "x")))),Abs("f",Abs("x", Var "x")));;

(*3*)
let rec print_terme t = match t with
	Cst c -> print_string c
	|Var x -> print_string x
	|Abs (x,e) ->print_string"(";print_string "\\";print_string x; print_string ".";print_terme e;print_string")"
	|App (t1,t2) -> print_string"(";print_terme t1;print_string" ";print_terme t2;print_string")";;

(*3.Variables libres et variables liées*)

(*1*)
let rec fv t = match t with
	Cst c -> []
	|Var x -> [x]
	|Abs (x,e) -> (suppr (fv e) x)
	|App (t1,t2) -> union (fv t1) (fv t2);;

(*2*)
let rec bv t = match t with 
	Cst c-> []
	|Var x -> []
	|Abs (x,e) -> if (suppr (fv e) x)=(fv e) then (bv e) else x::(bv e)
	|App (t1,t2) -> union (bv t1) (bv t2);;

(*3*)	
let rec vars t = match t with 
	Cst c-> []
	|Var x -> [x]
	|Abs (x,e) -> vars e
	|App (t1,t2) -> (vars t1)@(vars t2);;

(*4*)	
(*Fonction auxilliare représentant l'alphabet*)
let alphabet = ["a";"b";"c";"d";"e";"f";"g";"h";"i";"j";"k";"l";"m";"n";"o";"p";"q";"r";"s";"t";"u";"v";"w";"x";"y";"z"];;

let rec variable_fraiche alphabet l = match alphabet with
	[] -> "a"
	|t::r -> if (List.mem t l) then variable_fraiche r l else t;;

(*4.Substitution et renommage*)

(*1*)
let rec subst t x tr = match t with 
	Cst c -> t
	|Var v -> if not(v=x) then t else tr
	|Abs (a,b) -> if(List.mem x (fv b)) then Abs(a,(subst b x tr)) else Abs(a,b)
	|App (t1,t2) -> App(subst t1 x tr, subst t2 x tr);;

(*2*)
let rec alpha t x y = match t with 
	Cst c -> t
	|Var v -> if (x=v) then Var y else t
	|Abs (a,b) -> if((List.mem x (fv b)) && (a=x)) then Abs(y,subst b x (Var y)) else alpha(Abs(a,b)) x y
	|App (t1,t2) -> App(alpha t1 x y, alpha t2 x y);;
	
(*5. Réduction*)

(*1*)
let rec est_forme_normale t = match t with
	Cst c -> true
	|Var v -> true
	|Abs (a,b) -> true && est_forme_normale b
	|App(Abs(a1,a2),a3) -> false
	|App (t1,t2) -> est_forme_normale t1 && est_forme_normale t2;;

(*2*)

(*Fonction auxilliaire*)
let termes_remplacer a b = (inter (bv a) (fv b));;

(*Fonction auxilliaire permettant de faire l'alpha conversion*)
let alpha_total (App(Abs(a1,a2),a3)) = match (termes_remplacer a2 a3) with
	[] -> subst a2 a1 a3
	|t::r -> App(Abs(a1, (alpha a2 t (variable_fraiche alphabet (termes_remplacer a2 a3) ))),a3);;

let rec etape_NOR t = match t with
	Cst c -> Cst c
	|Var v -> Var v
	|Abs(a,b) -> Abs(a,etape_NOR b)
	|App(Abs(a1,a2),a3) -> alpha_total t
	|App(t1,t2) -> if(est_forme_normale t1) then App(t1,etape_NOR t2) else App(etape_NOR t1, t2);;
	
(*3*)					
let rec normalise t = if est_forme_normale t then t else normalise(etape_NOR t);;

(*6.Modélisation*)				

(*1*)
let vrai = Abs("x", Abs("y", Var "x"));;
let faux = Abs("x", Abs("y", Var "y"));;
let cond = Abs("c",Abs("v",Abs("f",App(App(Var "c",Var "v"),Var "f"))));;

print_terme (normalise(App(App(App(cond, vrai),Var "e1"),Var "e2")));;
print_terme (normalise(App(App(App(cond, faux),Var "e1"),Var "e2")));;

(*2*)
let succ = Abs("n",Abs("f",Abs("x",App( Var "f", App(App(Var "n",Var "f"), Var "x")))));;
let add = Abs("n",Abs("m",Abs("f",Abs("x",App(App(Var "n", Var "f"),App(App(Var "m", Var "f"), Var "x"))))));;
let mult = Abs("n",Abs("m",Abs("f",App(Var "m", App(Var "n", Var "f")))));;

let zero = Abs("f",Abs("x", Var "x"));;
let one = Abs("f",Abs("x", App(Var "f",Var "x")));;
let two = Abs("f",Abs("x", App(Var "f",App(Var "f",Var "x"))));;
let three = Abs("f",Abs("x", App(Var "f",App(Var "f",App(Var "f",Var "x")))));;

print_terme (normalise(App(succ,zero)));;
print_terme (normalise(App(App(add,one),two)));;
print_terme (normalise(App(App(mult,one),two)));;

(*3*)
let fst = Abs("t",App(Var "t", vrai));;
let snd = Abs("t",App(Var "t", faux));;
let iszero = Abs("n",App(App(Var "m", Abs("x",faux)),vrai));;
let pair = Abs("x",Abs("y",Abs("t",App(App(Var "t", Var "x"),Var "y"))));;
let pred = Abs("n",Abs("f",Abs("x",App(App(App(fst, App(Var "n",Abs("p", App( pair, App( snd, Var "p"))))),
			App(Var "f", App(snd , Var "p"))),Abs("t",App(App(Var "t", Var "x"), Var "x"))))));;

let comb_pt = App(Abs("x",Abs("y",App(Var "y",App(App(Var "x", Var "x"), Var "y")))),
				Abs("x",Abs("y",App(Var "y",App(App(Var "x", Var "x"), Var "y")))));;

let h = Abs("f",Abs("n", App(App(App(cond, App(iszero, Var "n")),one),App(App(mult, Var "n"),App(Var "f", App(pred, Var "n"))))));;

let fac = App(comb_pt,h);;
