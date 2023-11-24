solve_case_1:
        mov esi,string
        mov edi,string
        loop_in_solve_case_1:
            lodsb
            add al,byte [twenty]
            stosb
        loop loop_in_solve_case_1
    ret    