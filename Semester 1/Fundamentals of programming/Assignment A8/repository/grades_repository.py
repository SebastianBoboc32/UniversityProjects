from src.domain.grade import Grade
import copy
import random
import unittest


class GradesException(Exception):

    def __init__(self, message):
        self._message = message

    @property
    def message(self):
        return self._message


class GradesRepo:

    def __init__(self):
        self._data = []

    def add(self, grade):
        if grade in self._data:
            raise ValueError("Grade already in repo")
        self._data.append(grade)

    def get_by_student_id(self, stud_id):
        found = False
        for grd in self._data:
            if grd.student_id == stud_id:
                found = True
        if not found:
            raise ValueError("Student not found")
        result = list(filter(lambda grade: grade.student_id == stud_id, copy.deepcopy(self._data)))
        return result

    def get_by_assignment_id(self, assignment_id):
        found = False
        for grd in self._data:
            if grd.assignment_id == assignment_id:
                found = True
        if not found:
            raise ValueError("Assignment not found")
        result = list(filter(lambda grade: grade.assignment_id == assignment_id, copy.deepcopy(self._data)))
        return result

    def remove_by_student_id(self, student_id):
        found = False
        for grd in self._data:
            if grd.student_id == student_id:
                found = True
        if not found:
            raise ValueError("Student not found")
        result = list(filter(lambda grade: grade.student_id != student_id, copy.deepcopy(self._data)))
        self._data = copy.deepcopy(result)

    def remove_by_assigment_id(self, assignment_id):
        found = False
        for grd in self._data:
            if grd.assignment_id == assignment_id:
                found = True
        if not found:
            raise ValueError("Assignment not found")
        result = list(filter(lambda grade: grade.assignment_id != assignment_id, copy.deepcopy(self._data)))
        self._data = copy.deepcopy(result)

    def get_all(self):
        return list(self._data)

    def add_random(self):
        for _ in range(10):
            self.add(Grade(random.randint(1, 20), random.randint(1, 20), random.randint(1, 10)))
        for _ in range(10):
            self.add(Grade(random.randint(1, 20), random.randint(1, 20), None))


class TestGradesRepo(unittest.TestCase):
    def setUp(self) -> None:
        self.repo = GradesRepo()

    def test_empty_repo(self):
        self.assertEqual(len(self.repo.get_all()), 0)

    def test_adding_same_grade_twice(self):
        new_grade = Grade(11, 11, 7)
        self.repo.add(new_grade)
        with self.assertRaises(ValueError):
            self.repo.add(new_grade)

    def test_getting_by_invalid_student_id(self):
        new_grade = Grade(11, 11, 7)
        self.repo.add(new_grade)
        with self.assertRaises(ValueError):
            self.repo.get_by_student_id(81)

    def test_getting_by_invalid_assignment_id(self):
        new_grade = Grade(12, 13, 8)
        self.repo.add(new_grade)
        with self.assertRaises(ValueError):
            self.repo.get_by_assignment_id(133)

    def test_removing_by_invalid_student_id(self):
        new_grade = Grade(14, 16, 2)
        self.repo.add(new_grade)
        with self.assertRaises(ValueError):
            self.repo.remove_by_student_id(13)

    def test_removing_by_invalid_assignment_id(self):
        new_grade = Grade(11, 12, 4)
        self.repo.add(new_grade)
        with self.assertRaises(ValueError):
            self.repo.remove_by_assigment_id(1)


if __name__ == "__main__":
    unittest.main()
