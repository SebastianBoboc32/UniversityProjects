from src.domain.exceptions import A8ValidationException
from datetime import date


class AssignmentValidator:

    @staticmethod
    def validate(assignment):
        errors = []
        if type(assignment.deadline) != date:
            errors.append("Deadline must be a valid date DD/MM/YYYY")

        if type(assignment.assignment_id) != int:
            errors.append("The assignment id must be an integer")

        if type(assignment.description) != str:
            errors.append("Description must be a string")

        if assignment.description not in ["FP", "CSA", "Analysis", "Algebra", "Logic"]:
            errors.append("Unknown subject")

        if len(errors) > 0:
            raise A8ValidationException(errors)
