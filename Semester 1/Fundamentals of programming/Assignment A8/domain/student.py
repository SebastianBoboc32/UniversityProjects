import unittest


class Student:
    def __init__(self, student_id: int, group: int, name: str):
        self._student_id = student_id
        self._group = group
        self._name = name

    @property
    def student_id(self):
        return self._student_id

    @student_id.setter
    def student_id(self, new_id):
        self._student_id = new_id

    @property
    def group(self):
        return self._group

    @group.setter
    def group(self, new_group):
        self._group = new_group

    @property
    def name(self):
        return self._name

    @name.setter
    def name(self, new_name):
        self._name = new_name

    def __str__(self):
        return str(self._student_id) + ": " + self._name + " -> group: " + str(self._group)


class TestStudent(unittest.TestCase):
    def setUp(self) -> None:
        self.student_1 = Student(11, 911, "Boboc Sebastian")
        self.student_2 = Student(12, 917, "Boboc Sebastian-Andrei")

    def test_students(self):
        self.assertEqual(str(self.student_1), "11: Boboc Sebastian -> group: 911")
        self.assertEqual(str(self.student_2), "12: Boboc Sebastian-Andrei -> group: 917")
        self.student_1.group = 914
        self.assertEqual(self.student_1.group, 914)

    def test_data_types(self):
        self.assertIsInstance(self.student_1.student_id, int)
        self.assertIsInstance(self.student_1.group, int)
        self.assertIsInstance(self.student_1.name, str)
        self.assertIsInstance(self.student_2.student_id, int)
        self.assertIsInstance(self.student_2.group, int)
        self.assertIsInstance(self.student_2.name, str)


if __name__ == "__main__":
    unittest.main()
