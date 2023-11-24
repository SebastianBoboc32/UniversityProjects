isPowerOf2(X):-
    X =:=1.
isPowerOf2(X):-
    X mod 2 =:= 0,
    X1 is X//2,
    isPowerOf2(X1).

add_value_on_pow2([],_,[],_).
add_value_on_pow2([H|T],CurrentIndex,[H,ToBeAdded|L2],ToBeAdded):-
    isPowerOf2(CurrentIndex),
    NewIndex is CurrentIndex +1,
    add_value_on_pow2(T,NewIndex,L2,ToBeAdded).

add_value_on_pow2([H|T],CurrentIndex,[H|L2],ToBeAdded):-
    not(isPowerOf2(CurrentIndex)),
    NewIndex is CurrentIndex+1,
    add_value_on_pow2(T,NewIndex,L2,ToBeAdded).
