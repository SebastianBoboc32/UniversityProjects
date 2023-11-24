#
# The program's functions are implemented here. There is no user interaction in this file, therefore no input/print statements. Functions here
# communicate via function parameters, the return statement and raising of exceptions.
#


def add_result_of_new_participant(n1,n2,n3,table:list):
    assert type(n1) == int, str(n1)+" is not an integer"
    assert type(n2) == int, str(n2)+" is not an integer"
    assert type(n3) == int, str(n3)+" is not an integer"
    if n1 not in range(1, 11) or n2 not in range(1, 11) or n3 not in range(1, 11):
        raise ValueError("Grades out of range")
    else:
        table.append([n1, n2, n3])

#table = []

def add_grades_at_index(table:list,index:int,grades:list):
    index -= 1
    assert index < len(table), "participant "+str(index)+" isn't in the table"
    for i in range(len(grades)):
        num = grades[i]
        if type(num) != int or num not in range(1, 11):
            raise ValueError("Invalid grades")
    table[index] = grades[:]


def replace_grade_of_participant(table: list, index: int, problem: int, new_score: int):
    index -= 1
    assert type(new_score) == int, "The grade must be an integer"
    assert new_score in range(1, 11), "The grade must be between 1 and 10"
    if index not in range(0, len(table)):
        raise ValueError("Participant out of range")
    else:
        table[index][problem-1] = new_score


def remove_participant_scores(table:list, index:int):
    index -= 1
    assert index < len(table), "Participant "+str(index)+" isn't in the table"
    table[index] = [0, 0, 0]


def remove_more_participants_scores(table:list,start:int,stop:int):
    stop -= 1
    assert start >= 0 and start < len(table), "Invalid start index"
    assert stop >= 0 and stop < len(table), "Invalid stop index"
    assert stop > start
    for i in range(start, stop+1):
        table[i] = [0, 0, 0]


def average_grade_of_participant(table:list, index:int):
    assert index < len(table), "Participant "+str(index)+" is not in the table"
    suma = 0
    for i in range(3):
        suma += table[index][i]
    return suma / 3


def avgscore(arr:list):
    return arr[len(arr)-1]

def sorted_table(table:list):
    new_mat=[]
    for i in range(len(table)):
        new_mat.append([i+1, table[i], average_grade_of_participant(table, i)])

    new_mat.sort(key=avgscore, reverse=True)

    return new_mat



def sort_by_problem(table, n, pN):
    assert n < len(table) and n>=0, "List index out of range"
    if pN < 1 or pN > 3:
        raise ValueError("Problem "+str(pN)+" doesn't exist")
    else:
        new_table = table[:]
        for i in range(len(table)-1):
            for j in range(i+1,len(table)):
                if new_table[i][pN-1] < new_table[j][pN-1]:
                    new_table[i],new_table[j] = new_table[j],new_table[i]
        return new_table[:n]


def set_0_property(table, avgScore, symbol):
    if avgScore not in range(1,11):
        raise ValueError("Average score not in range")
    assert symbol in [">", "=", "<"], "Invalid symbol"
    if symbol == "=":
        for i in range(len(table)):
            if average_grade_of_participant(table, i) == avgScore:
                table[i] = [0, 0, 0]
    elif symbol == ">":
        for i in range(len(table)):
            if average_grade_of_participant(table, i) > avgScore:
                table[i] = [0, 0, 0]
    else:
        for i in range(len(table)):
            if average_grade_of_participant(table, i) < avgScore:
                table[i] = [0, 0, 0]
