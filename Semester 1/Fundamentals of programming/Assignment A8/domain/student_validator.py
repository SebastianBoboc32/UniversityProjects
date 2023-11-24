from src.domain.exceptions import A8ValidationException


class StudentValidator:

    @staticmethod
    def _is_group_valid(group):
        if type(group) != int:
            return False
        else:
            return group in range(911, 918)

    @staticmethod
    def validate(student):
        errors = []
        if not StudentValidator._is_group_valid(student.group):
            errors.append("Group should be between 911 and 917")

        if type(student.name) != str:
            errors.append("Name should be a string")

        elif " " not in student.name:
            errors.append("A student should have both a first name and a last name")

        if type(student.student_id) != int:
            errors.append("The id should be an integer")

        if len(errors) > 0:
            raise A8ValidationException(errors)
