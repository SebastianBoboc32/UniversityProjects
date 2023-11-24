from datetime import date
import unittest
from src.repository.grades_repository import GradesRepo
from src.repository.students_repository import StudentsRepo
from src.repository.assignments_repo import AssignmentsRepo
from src.services.assignments_service import AssignmentService
from src.services.students_service import StudentService
from src.domain.grade_validator import GradeValidator
from src.domain.student_validator import StudentValidator
from src.domain.assignment_validator import AssignmentValidator
from src.domain.grade import Grade
from src.domain.exceptions import A8ValidationException


class GradesDTO:
    def __init__(self, student, assignment):
        self._student = student
        self._assignment = assignment

    @property
    def student(self):
        return self._student

    @property
    def assignment(self):
        return self._assignment


class GradeService:
    def __init__(self, students_repo, assignments_repo, students_service, assignment_service, grades_repo, validator):
        self._students_repo = students_repo
        self._assignments_repo = assignments_repo
        self._students_service = students_service
        self._assignments_service = assignment_service
        self._repo = grades_repo
        self._validator = validator
        self._repo.add_random()

    def add(self, grade):
        self._validator.validate(grade)
        self._repo.add(grade)

    def get_by_student_id(self, student_id):
        return self._repo.get_by_student_id(student_id)

    def get_by_assignment_id(self, assignment_id):
        return self._repo.get_by_assignment_id(assignment_id)

    def get_all(self):
        return self._repo.get_all()

    def remove_by_student_id(self, student_id):
        self._repo.remove_by_student_id(student_id)

    def remove_by_assignment_id(self, assignment_id):
        self._repo.remove_by_student_id(assignment_id)

    # this method returns all students who received a given assignment, ordered descending by grade.
    def sort_by_descending_grade(self, assignment_id):
        result = []
        for grade in self._repo.get_all():
            if grade.assignment_id == assignment_id and grade.grade_value is not None:
                result.append([GradesDTO(self._students_service.get(grade.student_id), self._assignments_service.get(
                    grade.assignment_id)), grade.grade_value])
        result.sort(key=lambda x: x[1], reverse=True)
        return result

    # this method returns all students who are late in handing in at least one assignment.
    # These are all the students who have an ungraded assignment for which the deadline has passed.

    def late_students(self):
        result = []
        for grade in self._repo.get_all():
            if grade.grade_value is None:
                stud_id = grade.student_id
                assignment_id = grade.assignment_id
                assignment = self._assignments_repo.get(assignment_id)
                if date.today() > assignment.deadline:
                    result.append(GradesDTO(self._students_repo.get_by_id(stud_id), assignment))
        return result

    # this method returns Students with the best school situation,
    # sorted in descending order of the average grade received for all graded assignments.
    def best_students(self):
        students_grades = {}
        for_printing = []
        for grade in self._repo.get_all():
            if grade.grade_value is not None:
                if grade.student_id not in students_grades.keys():
                    students_grades[grade.student_id] = []
                    students_grades[grade.student_id].append(grade.grade_value)
        for stud in students_grades.keys():
            sum = 0
            counter = 0
            for grade in students_grades[stud]:
                sum += grade
                counter += 1
            students_grades[stud].append(float(sum)/float(counter))
        result = sorted(students_grades.items(), key=lambda x: x[len(x)-1], reverse=True)
        for student in result:
            for_printing.append([str(self._students_service.get(student[0])), student[len(student)-1][0]])
        return for_printing

    def assign_to_a_student(self, student_id, assignment_id):
        if assignment_id not in self._assignments_repo.all_assignment_ids():
            raise ValueError("Id not in repo")
        if student_id not in self._students_repo.all_student_ids():
            raise ValueError("Id not in repo")
        grd = Grade(student_id, assignment_id, None)
        if grd not in self._repo.get_all():
            self._repo.add(grd)

    def assign_to_a_group(self, group, assignment_id):
        if assignment_id not in self._assignments_repo.all_assignment_ids():
            raise ValueError("Id not in repo")
        group_of_students = self._students_repo.get_by_group(group)
        for stud in group_of_students:
            self._repo.add(Grade(stud.student_id, assignment_id, None))


class TestGradesRepo(unittest.TestCase):
    def setUp(self) -> None:
        students_repo = StudentsRepo()
        students_validator = StudentValidator()
        students_service = StudentService(students_repo, students_validator)
        assignments_repo = AssignmentsRepo()
        assignments_validator = AssignmentValidator()
        assignment_service = AssignmentService(assignments_repo, assignments_validator)
        grades_repo = GradesRepo()
        grades_validator = GradeValidator()
        grades_service = GradeService(students_repo, assignments_repo, students_service, assignment_service, grades_repo
                                      , grades_validator)
        self.grades_service = grades_service

    def test_add_invalid_grade(self):
        self.assertEqual(len(self.grades_service.get_all()), 20)
        new_grade = Grade(2, 11, "xx")
        try:
            self.grades_service.add(new_grade)
        except A8ValidationException:
            assert True

    def test_getting_non_existent_by_stud_id(self):
        with self.assertRaises(ValueError):
            self.grades_service.get_by_student_id(777)

    def test_getting_non_existent_by_assignment_id(self):
        with self.assertRaises(ValueError):
            self.grades_service.get_by_assignment_id(777)

    def test_remove_non_existent_student_id(self):
        self.grades_service.remove_by_student_id(10)
        with self.assertRaises(ValueError):
            self.grades_service.remove_by_student_id(60)

    def test_remove_non_existent_assignment_id(self):
        self.grades_service.remove_by_assignment_id(12)
        with self.assertRaises(ValueError):
            self.grades_service.remove_by_assignment_id(60)

    def test_assign_to_a_student(self):
        self.grades_service.assign_to_a_student(10, 11)
        with self.assertRaises(ValueError):
            self.grades_service.assign_to_a_student(60, 61)
            self.grades_service.assign_to_a_student(10, 85)
            self.grades_service.assign_to_a_student(55, 9)

    def test_assign_to_a_group(self):
        self.grades_service.assign_to_a_group(911, 13)
        with self.assertRaises(ValueError):
            self.grades_service.assign_to_a_group(920, 11)
            self.grades_service.assign_to_a_group(921, 900)
            self.grades_service.assign_to_a_group(10, 100)


if __name__ == "__main__":
    unittest.main()

