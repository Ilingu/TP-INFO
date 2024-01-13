type 'a anb = Nn of 'a * 'a anb list

type 'a abns =
  | V
  | N of 'a * 'a abns * 'a abns

let rec vers_binaire (arbre:('a anb)): 'a abns =
  let rec aux (current:('a anb)) siblings =
    match current, siblings with
    | Nn (e, []), [] -> N(e, V, V)
    | Nn (e, f::fs), [] -> N(e, aux f fs, V)
    | Nn (e, []), b::bs -> N(e, V, aux b bs)
    | Nn (e, f::fs), b::bs -> N(e, aux f fs, aux b bs)
  in
  aux arbre []

(* let rec vers_naire (arbre:('a abns)): 'a anb =
  let rec aux (current:('a abns)) =
    match current with
    | N (e, V, V) -> (Nn(e,[]), [])
    | N (e, V, sib) -> (N(e, ), sib)
    | N (e, kids, V) -> (N(e, ), sib)
    | N (e, kids, sib) -> (N(e, ), sib)
    | V -> failwith ""
  in
  let (a, _) = aux arbre in
  a *)