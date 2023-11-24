from src.domain.student import Student
import random
import unittest


class StudentsRepoException(Exception):
    def __init__(self, message):
        self._message = message

    @property
    def message(self):
        return self._message


class StudentsRepo:

    def __init__(self):
        self._data = {}

    def add_student(self, student):
        if student.student_id in self._data.keys():
            raise ValueError("Student already in repo")
        self._data[student.student_id] = student

    def get_by_id(self, stud_id):
        if stud_id not in self._data.keys():
            raise ValueError("Student not in the repo")
        return self._data[stud_id]

    def all_student_ids(self):
        return list(self._data.keys())

    def get_all_names(self):
        result = []
        for stud in self._data.values():
            result.append(stud.name)
        return result

    def all_groups(self):
        result = []
        for student in self._data.values():
            result.append(student.group)
        return result

    def get_by_group(self, group):
        if group not in self.all_groups():
            raise ValueError("Invalid group")
        result = []
        for student_id in self._data.keys():
            student = self.get_by_id(student_id)
            if student.group == group:
                result.append(student)
        return result

    def remove(self, student_id):
        if student_id not in self._data.keys():
            raise ValueError("Student not in the repo")
        del self._data[student_id]

    def add_random(self):
        first_names = ["Sebastian", "Gabriel", "Andrei", "Andreea", "Alexandra", "Rares", "Madalin", "Gabriela"]
        last_names = ["Popescu", "Boboc", "Birou", "Bica", "Ionescu", "Andrei"]
        full_name = random.choice(first_names) + " " + random.choice(last_names)
        while full_name in self.get_all_names():
            full_name = random.choice(first_names) + " " + random.choice(last_names)
        _id = len(self._data) + 1
        group = random.randint(911, 917)
        self._data[_id] = Student(_id, group, full_name)

    def get_all(self):
        return list(self._data.values())

    def change_group(self, student_id, new_group):
        self._data[student_id].group = new_group

    def change_name(self, student_id, new_name):
        self._data[student_id].name = new_name


class TestStudentsRepo(unittest.TestCase):

    def setUp(self) -> None:
        self.repo = StudentsRepo()

    def test_empty_repo(self):
        self.assertEqual(len(self.repo.get_all()), 0)
        self.assertEqual(len(self.repo.all_groups()), 0)
        self.assertEqual(len(self.repo.get_all_names()), 0)

    def test_adding_same_student_twice(self):
        new_student = Student(11, 911, "Boboc Sebastian-Andrei")
        self.repo.add_student(new_student)
        with self.assertRaises(ValueError):
            self.repo.add_student(new_student)

    def test_get_by_invalid_id(self):
        with self.assertRaises(ValueError):
            self.repo.get_by_id(103)

    def test_get_by_invalid_group(self):
        with self.assertRaises(ValueError):
            self.repo.get_by_group(918)

    def test_removing_non_existent_student(self):
        with self.assertRaises(ValueError):
            self.repo.remove(7)


if __name__ == "__main__":
    unittest.main()
