from src.domain.exceptions import A8ValidationException
from src.domain.grade import Grade


class GradeValidator:

    @staticmethod
    def validate(grade:Grade):
        errors = []
        if type(grade.grade_value) != int and grade.grade_value not in range(1, 11):
            errors.append("Grade should be an integer between 1 and 10")

        if type(grade.student_id) != int:
            errors.append("Student id should be an integer")

        if type(grade.assignment_id) != int:
            errors.append("Assignment id should be an integer")

        if len(errors) > 0:
            raise A8ValidationException(errors)
