from src.domain.student import Student
from src.domain.assignment import Assignment
from src.domain.grade import Grade
from datetime import date


class UserInterface:
    def __init__(self, grades_service, assignment_service, students_service):
        self._grades_service = grades_service
        self._assignment_service = assignment_service
        self._students_service = students_service

    def print_all_students(self):
        result = self._students_service.get_all()
        for stud in result:
            print(str(stud))

    def print_all_assignments(self):
        result = self._assignment_service.get_all()
        for assignment in result:
            print(str(assignment))

    def print_all_grades(self):
        result = self._grades_service.get_all()
        for grade in result:
            print(str(grade))

    def print_all_late_students(self):
        result = self._grades_service.late_students()
        for obj in result:
            print(str(obj.student) + " late in " + str(obj.assignment))

    def print_best_students(self):
        result = self._grades_service.best_students()
        for student in result:
            print(str(student))

    def print_by_assigment_id(self, assignment_id):
        result = self._grades_service.sort_by_descending_grade(assignment_id)
        for obj in result:
            print(str(obj[0].student) + " -> " + str(obj[0].assignment))

    def menu(self):
        while True:
            print("1.Display all students")
            print("2.Display all assignments")
            print("3.Display all grades")
            print("4.Display the students decreasingly by their average")
            print("5.Display all students that haven't returned assignments in time")
            print("6.Display the students decreasingly by a grade at a specific assignment")
            print("7.Add a student")
            print("8.Add an assignment")
            print("9.Add a grade")
            print("10.Assign an assignment to a student")
            print("11.Assign an assignment to a group")
            print("12.Update a student")
            print("13.Update an assignment")
            print("0.Exit")
            token = int(input("Select an action"))
            if token == 0:
                return
            elif token == 1:
                self.print_all_students()
            elif token == 2:
                self.print_all_assignments()
            elif token == 3:
                self.print_all_grades()
            elif token == 4:
                self.print_best_students()
            elif token == 5:
                self.print_all_late_students()
            elif token == 6:
                assignment_id = int(input("Select the assignment id"))
                try:
                    self.print_by_assigment_id(assignment_id)
                except ValueError:
                    print("invalid id")
            elif token == 7:
                name = input("Name: ")
                stud_id = int(input("ID: "))
                group = int(input("Group: "))
                try:
                    self._students_service.add(Student(stud_id, group, name))
                except Exception:
                    print("Can't add this student")

            elif token == 8:
                assignment_id = int(input("ID: "))
                print("Choose a deadline")
                year = int(input("Year: "))
                month = int(input("Month: "))
                day = int(input("Day: "))
                deadline = date(year, month, day)
                description = input("Description: ")
                try:
                    self._assignment_service.add(Assignment(assignment_id, description, deadline))
                except Exception:
                    print("Can't add this assignment!")
            elif token == 9:
                student_id = int(input("Student id: "))
                assignment_id = int(input("Assignment id: "))
                value = int(input("Value: "))
                grd = Grade(student_id, assignment_id, value)
                try:
                    self._grades_service.add(grd)
                except Exception:
                    print("Can't add this grade")
            elif token == 10:
                student_id = int(input("Student id: "))
                assignment_id = int(input("Assignment id: "))
                try:
                    self._grades_service.assign_to_a_student(student_id, assignment_id)
                except Exception:
                    print("Can't assign this")
            elif token == 11:
                group = int(input("Group: "))
                assignment_id = int(input("Assignment id: "))
                try:
                    self._grades_service.assign_to_a_group(group, assignment_id)
                except Exception:
                    print("Something was wrong :/")
            elif token == 12:
                student_id = int(input("Which student you'd like to update/delete?"))
                try:
                    self._students_service.get(student_id)
                except Exception:
                    print("Couldn't get this student")
                action = input("change/remove")
                if action == "change":
                    change = input("What to change?")
                    if change == "name":
                        new_name = input("Select the name")
                        try:
                            self._students_service.change_name(student_id, new_name)
                        except Exception:
                            print("Can't make this change :/")
                    elif change == "group":
                        new_group = int(input("Select the group"))
                        try:
                            self._students_service.change_group(student_id, new_group)
                        except Exception:
                            print("Can't make this change :/")
                    else:
                        raise ValueError("Invalid attribute")
                elif action == "remove":
                    try:
                        self._students_service.remove(student_id)
                    except Exception:
                        print("Student not found")
                else:
                    raise ValueError("Invalid action")
            elif token == 13:
                assignment_id = int(input("Which assignment you'd like to update/delete?"))
                try:
                    self._assignment_service.get(assignment_id)
                except Exception:
                    print("Assignment not found")
                action = input("change/remove")
                if action == "change":
                    change = input("What to change?")
                    if change == "description":
                        new_description = input("Select the new description")
                        try:
                            self._assignment_service.change_description(assignment_id, new_description)
                        except Exception:
                            print("Couldn't make the change")
                    elif change == "deadline":
                        day = int(input("Select a new day: "))
                        month = int(input("Select a new month"))
                        year = int(input("Select a new year: "))
                        try:
                            self._assignment_service.change_deadline(assignment_id, date(year, month, day))
                        except Exception:
                            print("Couldn't change the deadline")
                    else:
                        raise ValueError("Invalid attribute")
                elif action == "remove":
                    try:
                        self._assignment_service.remove(assignment_id)
                    except Exception:
                        print("Nothing to remove")
                else:
                    raise ValueError("Invalid Action")    





