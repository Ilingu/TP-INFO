type ('n,'f) arbre = 
| Feuille of 'f
| Noeud of 'n * ('n, 'f) arbre * ('n, 'f) arbre

type ('n,'f) token = 
| N of 'n
| F of 'f

type 'a file = 'a list * 'a list

let push x ((e,s):'a file) :'a file = (x::e, s)

let pop ((e,s):'a file) :'a * 'a file = 
    match s with
    | [] -> (
        match List.rev e with
        | [] -> failwith "nothing to extract"
        | h::t -> (h, ([], t))
    )
    | h::t -> (h, (e, t))
    
let is_empty (f:'a file) =
    match f with
    | ([],[]) -> true
    | _ -> false

let lire_postfixe (tok_list:('n,'f)token list): ('n,'f)arbre = 
  let rec aux (foret: ('n,'f)arbre list) (tok_list: ('n,'f)token list): ('n,'f)arbre list =
    match tok_list with
    | [] -> foret
    | h::t -> (
        match h with
        | N e -> (
            match foret with
            | [] -> failwith "not possible"
            | h1::[] -> failwith "not possible: strict"
            | h1::h2::tf -> aux (Noeud(e,h2,h1)::tf) t
        )    
        | F e -> aux ((Feuille e)::foret) t
    )
  in
  match aux [] tok_list with
  | [] -> failwith ""
  | h::t -> h

let lire_prefixe (tok_list:('n,'f)token list): ('n,'f)arbre = 
  let rec aux (foret: ('n,'f)arbre list) (tok_list: ('n,'f)token list): ('n,'f)arbre =
    match (tok_list, foret) with
    | ((N e)::t, h1::h2::f) -> aux (Noeud(e,h1,h2)::f) t
    | ((F e)::t, _) -> aux ((Feuille e)::foret) t
    | ([], [arbre]) -> arbre
    | _ -> failwith "fail"
  in
  aux [] (List.rev tok_list)


let lire_largeur u = 
  let rec aux f u =
    match u with
    | F x::xs ->
      let f = push (Feuille x) f in
      aux f xs
    | N x::xs ->
      let d,f = pop f in
      let g,f = pop f in
      let f = push (Noeud(x,g,d)) f in
      aux f xs
    | [] ->
      let a,f = pop f in
      if is_empty f then a else failwith "fail"
  in
  aux ([],[]) u

(* let res = lire_prefixe [N 12; N 4; F 7; N 14; F 1; F 2; F 20];; *)
