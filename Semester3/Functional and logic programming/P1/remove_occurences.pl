remove_occurences(_,[],[]).
remove_occurences(X,[X|T],L2) :-remove_occurences(X,T,L2).
remove_occurences(X,[Y|T],[Y|L2]):-
    X =\=Y,
    remove_occurences(X,T,L2).
