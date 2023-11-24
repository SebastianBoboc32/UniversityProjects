from src.domain.assignment import Assignment
from datetime import date
import random
import unittest


class AssignmentRepoException(Exception):
    def __init__(self, msg):
        self._message = msg

    @property
    def message(self):
        return self._message


class AssignmentsRepo:

    def __init__(self):
        self._data = {}

    def add(self, assignment):
        if assignment.assignment_id in self._data.keys():
            raise ValueError("Task already assigned")
        self._data[assignment.assignment_id] = assignment

    def all_assignment_ids(self):
        return list(self._data.keys())

    def add_rand(self):
        assignment_id = len(self._data) + 1
        subjects = ["CSA", "FP", "Analysis", "Algebra", "Logic"]
        description = random.choice(subjects)
        year = random.randint(2022, 2023)
        month = random.randint(1, 12)
        if month in [1, 3, 5, 7, 8, 10, 12]:
            day = random.randint(1, 31)
        elif month == 2:
            day = random.randint(1, 28)
        else:
            day = random.randint(1, 30)
        self._data[assignment_id] = Assignment(assignment_id, description, date(year, month, day))

    def get(self, assigment_id):
        if assigment_id not in self._data.keys():
            raise KeyError("Invalid assignment id")
        return self._data[assigment_id]

    def remove(self, assignment_id):
        if assignment_id not in self._data.keys():
            raise KeyError("Invalid assignment id")
        del self._data[assignment_id]

    def get_all(self):
        return list(self._data.values())

    def change_description(self, assignment_id, new_desc):
        self._data[assignment_id].description = new_desc

    def change_deadline(self, assignment_id, new_dead_line):
        self._data[assignment_id].deadline = new_dead_line


class TestAssignmentsRepo(unittest.TestCase):
    def setUp(self) -> None:
        self.repo = AssignmentsRepo()

    def test_empty_repo(self):
        self.assertEqual(len(self.repo.get_all()), 0)

    def test_adding_assignment_twice(self):
        new_assignment = Assignment(11, "FP", date(2022, 5, 22))
        self.repo.add(new_assignment)
        with self.assertRaises(ValueError):
            self.repo.add(new_assignment)

    def test_getting_non_existent_assignment(self):
        new_assignment = Assignment(11, "FP", date(2022, 5, 22))
        self.repo.add(new_assignment)
        with self.assertRaises(KeyError):
            self.repo.get(12)

    def test_removing_non_existent_assignment(self):
        new_assignment = Assignment(11, "FP", date(2022, 5, 22))
        self.repo.add(new_assignment)
        with self.assertRaises(KeyError):
            self.repo.remove(13)


if __name__ == "__main__":
    unittest.main()
