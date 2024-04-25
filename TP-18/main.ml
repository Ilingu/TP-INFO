
let swap arr i j =
    let tempi = arr.(i) in
    arr.(i) <- arr.(j);
    arr.(j) <- tempi;;

let renverse arr =
    let n = Array.length arr in
    for i = 0 to n/2-1 do
        swap arr i (n-1-i);
    done;;

let occurrences x arr =
    let occ = ref []; 
    let n = Array.length arr in
    for i = 0 to n-1 do
        let mir = n-1-i in 
        if arr.(mir) = x then 
            occ := mir::(!occ)
    done;
    !occ