#
# This is the program's UI module. The user interface and all interaction with the user (print and input statements) are found here
#
import functions
import random
import copy

def print_all(table:list):
    for i in range(len(table)):
        print(str(i+1)+".  "+str(table[i][0])+"|"+str(table[i][1])+"|"+str(table[i][2]))

def print_sorted_table(table,n):
    assert n <= len(table), "List index out of range"
    output = functions.sorted_table(table)
    for i in range(n):
        print("number "+str(i+1)+" is: "+str(output[i][0])+" with grades "+str(output[i][1])+" and average "+str(output[i][2]))

def print_property(table,symbol,number, problem):
    assert number in range (1,11), "Invalid comparison grade"
    assert problem in range(1,4), "Problem "+str(problem)+" doesn't exist"
    if symbol not in [">", "=", "<"]:
        raise ValueError("Invalid symbol")
    if symbol == "=":
        output = []
        for i in range(len(table)):
            if table[i][problem-1] == number:
                output.append(table[i][:])
        print_all(output)
    elif symbol == ">":
        output = []
        for i in range(len(table)):
            if table[i][problem-1] > number:
                output.append(table[i][:])
        print_all(output)
    elif symbol == "<":
        output = []
        for i in range(len(table)):
            if table[i][problem-1] < number:
                output.append(table[i][:])
        print_all(output)

def user_interface():
    cont = True
    board = []
    archive = []
    for i in range(10):
        arr = []
        for j in range(3):
            arr.append(random.randint(1, 10))
        board.append(arr)

    archive.append(copy.deepcopy(board))

    while True:
        print("Add new participant to the board")
        print("Insert grades at a specified participant")
        print("Remove the grades of a specified participant")
        print("Remove the grades of a range of participants")
        print("Change the grade of a problem ")
        print("Set the participants grades with an average bigger smaller or equal than a number to 0")
        print("Print the entire table")
        print("Print the participants who got > | = | < at a problem than a specified score")
        print("Print the list of scores decreasingly")
        print("Print the podium")
        print("Print the participants with the biggest score at specified problem")
        print("Undo")
        print("Exit")
        option = input("Write the desired command")
        option.strip()
        partition = option.split()
        name = partition[0]
        #parametres = partition[1:]
        if name == "add":
            p1 = int(partition[1])
            p2 = int(partition[2])
            p3 = int(partition[3])
            functions.add_result_of_new_participant(p1, p2, p3, board)
            archive.append(copy.deepcopy(board))

        elif name == "insert":
            p1 = int(partition[1])
            p2 = int(partition[2])
            p3 = int(partition[3])
            index = int(partition[5])
            functions.add_grades_at_index(board, index, [p1, p2, p3])
            archive.append(copy.deepcopy(board))

        elif name == "remove" and len(partition)==2:
            index = int(partition[1])
            functions.remove_participant_scores(board, index)
            archive.append(copy.deepcopy(board))

        elif name == "remove" and len(partition)>2:
            start = int(partition[1])
            stop = int(partition[3])
            functions.remove_more_participants_scores(board, start, stop)
            archive.append(copy.deepcopy(board))

        elif name == "replace":
            participant = int(partition[1])
            problem = partition[2]
            if problem == "P1":
                p_n = 1
            elif problem == "P2":
                p_n = 2
            elif problem == "P3":
                p_n = 3
            else:
                raise ValueError("invalid problem statement")
            new_grade = int(partition[4])
            functions.replace_grade_of_participant(board, participant, p_n, new_grade)
            archive.append(copy.deepcopy(board))

        elif name == "list" and len(partition)==1:
            print_all(board)

        elif name == "list" and partition[1] == "sorted":
            print_sorted_table(board, len(board))

        elif name == "list" and len(partition) == 3:
            symbol = partition[1]
            grade = int(partition[2])
        elif option == 8:
            grade = int(input("Select the grade of the comparison"))
            print("Select between bigger,equal or smaller")
            symbol = input("Press > for bigger , = for equal or < for smaller")
            pb = int(input("Select the problem"))
            print_property(board, symbol, grade, pb)

        elif option == 9:
            print_sorted_table(board, len(board))

        elif option == 10:
            size = int(input("Select the size of the podium"))
            if size >= len(board):
                print_sorted_table(board, len(board))
            else:
                print_sorted_table(board, size)

        elif option == 11:
            problem = int(input("Select the problem"))
            nr = int(input("Select the number of participants with the highest grade obtained in problem "+str(problem)))
            print_sorted_table(board, nr)

        elif option == 12:
            if len(archive) < 2:
                print("Nothing to undo!")
            else:
                board = copy.deepcopy(archive[len(archive)-2])
                X = archive.pop()

        elif option == 13:
            return

        else:
            print("Unknown command")
            return
