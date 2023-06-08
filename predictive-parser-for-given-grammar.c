//assuming the grammar is left-recursion eliminated

/*let grammar be:
E->TE'
E'->+TE'|e                 e=EPSILON
T->FT'
T'->*FT'
F->(E)
F->id

