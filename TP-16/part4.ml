type op =
  | Plus
  | Fois
  | Moins

type expr = 
  | C of int
  | N of op * expr * expr

let exemple1 = N(Plus, N(Fois, C 4, N(Moins, C 8, C 9)), N(Plus, C 6, C 7))
let exemple2 = N(Plus, C 2, N(Fois, C 4, C 3))
let exemple3 = N(Fois, C 4, N(Plus, C 2, C 3))

let rec applique (ops:op) (infixe:int) (postfixe:int): int = 
  match ops with
  | Plus -> infixe+postfixe
  | Fois -> infixe*postfixe
  | Moins -> infixe-postfixe

let rec eval (expression:expr): int =
  match expression with
  | C e -> e
  | N(ops, a, b) -> applique ops (eval a) (eval b)

let res = eval exemple2;