from datetime import date
import unittest


class Assignment:
    def __init__(self, assignment_id: int, description: str, deadline: date):
        self._assignment_id = assignment_id
        self._description = description
        self._deadline = deadline

    @property
    def assignment_id(self):
        return self._assignment_id

    @assignment_id.setter
    def assignment_id(self, new_id):
        self._assignment_id = new_id

    @property
    def description(self):
        return self._description

    @description.setter
    def description(self, new_desc):
        self._description = new_desc

    @property
    def deadline(self):
        return self._deadline

    @deadline.setter
    def deadline(self, new_deadline):
        self._deadline = new_deadline

    def __str__(self):
        return str(self._assignment_id)+": " + self._description + " -> " + self._deadline.strftime("%d.%m.%Y")


class TestAssigment(unittest.TestCase):

    def setUp(self):
        self.assignment_1 = Assignment(1, "FP", date(2022, 3, 25))
        self.assignment_2 = Assignment(2, "CSA", date(2022, 5, 20))

    def test_assignments(self):
        self.assertEqual(str(self.assignment_1), "1: FP -> 25.03.2022")
        self.assertEqual(str(self.assignment_2), "2: CSA -> 20.05.2022")
        self.assignment_1.description = "Logic"
        self.assertEqual(self.assignment_1.description, "Logic")

    def test_data_types(self):
        self.assertIsInstance(self.assignment_1.deadline, date)
        self.assertIsInstance(self.assignment_2.deadline, date)
        self.assertIsInstance(self.assignment_1.assignment_id, int)
        self.assertIsInstance(self.assignment_2.assignment_id, int)
        self.assertIsInstance(self.assignment_1.description, str)
        self.assertIsInstance(self.assignment_2.description, str)


if __name__ == "__main__":
    unittest.main()
