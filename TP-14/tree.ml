type ('n, 'f) abs =
  | Feuille of 'f
  | Noeud of 'n * ('n, 'f) abs * ('n, 'f) abs

type 'a abns =
  | V
  | N of 'a * 'a abns * 'a abns

let exemple1 =
Noeud
( 12
, Noeud
( 4
, Noeud (7, Feuille 20, Feuille 30)
, Noeud (14, Feuille 1, Feuille 2) )
, Feuille 20 )

let exemple2 = N(4.0, N(0.3, V, V), N(1.0, N(8.0, N(2.0, N(2.5,V,V), N(3.1,V,V)), N(4.1,V,V)), N(0.2,V,V)))

let rec hauteurAbs (a:(int,int)abs):int =
  match a with
  | Feuille(_) -> 0
  | Noeud(_,g,d) -> 1 + max (hauteurAbs g) (hauteurAbs d)

let () = Printf.printf "%d\n" (hauteurAbs exemple1)

let rec tailleAbs (a:(int,int)abs):int =
  match a with
  | Feuille(_) -> 1
  | Noeud(_,g,d) -> 1 + (tailleAbs g) + (tailleAbs d)

let () = Printf.printf "%d\n" (tailleAbs exemple1)

let rec dernierAbs (a:(int,int)abs):int =
  match a with
  | Feuille(e) -> e
  | Noeud(_,_,d) -> dernierAbs d

let () = Printf.printf "%d\n" (dernierAbs exemple1)

let rec hauteurAbns (a:(float)abns):int =
  match a with
  | V -> -1
  | N(_,g,d) -> 1 + max (hauteurAbns g) (hauteurAbns d)

let () = Printf.printf "%d\n" (hauteurAbns exemple2)

let rec tailleAbns (a:(float)abns):int =
  match a with
  | V -> 0
  | N(_,g,d) -> 1 + (tailleAbns g) + (tailleAbns d)

let () = Printf.printf "%d\n" (tailleAbns exemple2)

let rec dernierAbns (a:(float)abns):float =
  match a with
  | V -> failwith "Vide"
  | N(e,_,d) ->
     match d with
     | V -> e
     | _ -> dernierAbns d

let () = Printf.printf "%f\n" (dernierAbns exemple2)

let rec ont_meme_squelette (a:(float)abns) (b:(float)abns):bool =
  match a with
  | V -> (match b with
          | V -> true
          | _ -> false)
  | N(_,g1,d1) -> (match b with
                | N(  _,g2,d2) -> ont_meme_squelette g1 g2 && ont_meme_squelette d1 d2
                | _ -> false)

let () = Printf.printf "%b\n" (ont_meme_squelette exemple2 exemple2)

let rec pow a n =
  match a with
  | 0 -> 1
  | _ -> if n mod 2 = 0 then pow (a*a) (n/2) else a*(pow (a*a) (n/2))

let est_parfait (a:(int,int)abs):bool = 
  tailleAbs a = pow (2) (hauteurAbs (a) + 1) -1

let exemple3 = Noeud(1, Feuille(2), Feuille(3))

let () = Printf.printf "%b\n" (est_parfait exemple3)

let miroir (a:(float)abns):(float)abns =
  match a with
  | V -> V
  | N(e,d,g) -> (match scrutinee with
                  | pattern -> pattern
                )

let est_symetrique (a:(float)abns):bool =
  match a with
  | V -> 
  | 