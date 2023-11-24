import unittest


class Grade:
    def __init__(self, student_id: int, assignment_id: int, grade_value):
        self._student_id = student_id
        self._assignment_id = assignment_id
        self._grade_value = grade_value

    @property
    def student_id(self):
        return self._student_id

    @student_id.setter
    def student_id(self, new_value):
        self._student_id = new_value

    @property
    def assignment_id(self):
        return self._assignment_id

    @assignment_id.setter
    def assignment_id(self, new_value):
        self._assignment_id = new_value

    @property
    def grade_value(self):
        return self._grade_value

    @grade_value.setter
    def grade_value(self, new_value):
        self._grade_value = new_value

    def __str__(self):
        return " assignment id: " + str(self._assignment_id) + "-> student id: " + \
            str(self._student_id) + "-> grade: " + str(self._grade_value)


class TestGrade(unittest.TestCase):

    def setUp(self):
        self.grade_1 = Grade(1, 1, 9)
        self.grade_2 = Grade(2, 2, 8)

    def test_grades(self):

        self.assertEqual(str(self.grade_1), " assignment id: 1-> student id: 1-> grade: 9")
        self.assertEqual(str(self.grade_2), " assignment id: 2-> student id: 2-> grade: 8")
        self.grade_2.grade_value = 10
        self.assertEqual(self.grade_2.grade_value, 10)

    def test_data_types(self):
        self.assertIsInstance(self.grade_1.grade_value, int)
        self.assertIsInstance(self.grade_1.student_id, int)
        self.assertIsInstance(self.grade_1.assignment_id, int)
        self.assertIsInstance(self.grade_2.grade_value, int)
        self.assertIsInstance(self.grade_2.student_id, int)
        self.assertIsInstance(self.grade_2.assignment_id, int)


if __name__ == "__main__":
    unittest.main()

