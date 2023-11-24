from src.domain.assignment import Assignment
from src.domain.assignment_validator import AssignmentValidator
from src.repository.assignments_repo import AssignmentsRepo
from datetime import date
from src.domain.exceptions import A8ValidationException
import unittest


class AssignmentService:
    def __init__(self, repo, valid):
        self._repo = repo
        self._validator = valid
        for _ in range(20):
            self._repo.add_rand()

    def add(self, assignment):
        self._validator.validate(assignment)
        self._repo.add(assignment)

    def get(self, assignment_id):
        return self._repo.get(assignment_id)

    def add_random(self):
        self._repo.add_rand()

    def get_all(self):
        return self._repo.get_all()

    def remove(self, assignment_id):
        self._repo.remove(assignment_id)

    def change_deadline(self, assignment_id, new_deadline):
        self._repo.change_deadline(assignment_id, new_deadline)

    def change_description(self, assignment_id, new_description):
        self._repo.change_description(assignment_id, new_description)


class TestAssignmentsService(unittest.TestCase):
    def setUp(self) -> None:
        assignments_repo = AssignmentsRepo()
        assignments_validator = AssignmentValidator()
        self.assignments_service = AssignmentService(assignments_repo, assignments_validator)

    def test_add_invalid_assignment(self):
        invalid_assignment = Assignment("1", "CSA", date(2022, 6, 11))
        try:
            self.assignments_service.add(invalid_assignment)
        except A8ValidationException:
            assert True

    def test_getting_invalid_assignment(self):
        with self.assertRaises(KeyError):
            self.assignments_service.get(44)

    def test_remove_non_existent_assignment(self):
        with self.assertRaises(KeyError):
            self.assignments_service.remove(66)

    def test_change_deadline(self):
        new_deadline = 14
        try:
            self.assignments_service.change_deadline(11, new_deadline)
        except A8ValidationException:
            assert True

    def test_change_description(self):
        new_description = date(2022, 4, 2)
        try:
            self.assignments_service.change_description(10, new_description)
        except A8ValidationException:
            assert True


if __name__ == "__main__":
    unittest.main()

