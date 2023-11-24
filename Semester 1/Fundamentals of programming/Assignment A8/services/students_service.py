from src.domain.student_validator import StudentValidator
from src.repository.students_repository import StudentsRepo, StudentsRepoException
from src.domain.student import Student
import unittest
from src.domain.exceptions import A8ValidationException


class StudentService:

    def __init__(self, repo, validator):
        self._repo = repo
        self._validator = validator
        for _ in range(20):
            self._repo.add_random()

    def add(self, student):
        self._validator.validate(student)
        self._repo.add_student(student)

    def get(self, stud_id):
        return self._repo.get_by_id(stud_id)

    def add_random(self):
        self._repo.add_random()

    def remove(self, stud_id):
        self._repo.remove(stud_id)

    def get_all(self):
        return self._repo.get_all()

    def change_group(self, student_id, new_group):
        if type(new_group) != int:
            raise TypeError("Group should be an integer")
        self._repo.change_group(student_id, new_group)

    def change_name(self, student_id, new_name):
        if type(new_name) != str:
            raise TypeError("Name should be a string")
        self._repo.change_name(student_id, new_name)


class TestStudentsService(unittest.TestCase):
    def setUp(self) -> None:
        stud_repo = StudentsRepo()
        stud_validator = StudentValidator()
        self.students_service = StudentService(stud_repo, stud_validator)

    def test_adding_invalid_student(self):
        new_stud = Student("1", "00", 22)
        try:
            self.students_service.add(new_stud)
        except A8ValidationException:
            assert True

    def test_getting_non_existent_student(self):
        self.students_service.get(10)
        with self.assertRaises(ValueError):
            self.students_service.get(404)

    def test_removing_non_existent_student(self):
        self.students_service.remove(12)
        with self.assertRaises(ValueError):
            self.students_service.remove(23)

    def test_changing_group(self):
        new_group = "911"
        with self.assertRaises(TypeError):
            self.students_service.change_group(new_group)

    def test_changing_name(self):
        new_name = 11
        with self.assertRaises(TypeError):
            self.students_service.change_name(new_name)


if __name__ == "__main__":
    unittest.main()

