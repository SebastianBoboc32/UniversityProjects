from src.ui.ui import UserInterface
from src.services.students_service import StudentService
from src.services.grades_service import GradeService
from src.services.assignments_service import AssignmentService
from src.repository.students_repository import StudentsRepo
from src.repository.assignments_repo import AssignmentsRepo
from src.repository.grades_repository import GradesRepo
from src.domain.grade_validator import GradeValidator
from src.domain.student_validator import StudentValidator
from src.domain.assignment_validator import AssignmentValidator

if __name__ == "__main__":
    assignment_repo = AssignmentsRepo()
    students_repo = StudentsRepo()
    grades_repo = GradesRepo()
    assignment_validator = AssignmentValidator()
    students_validator = StudentValidator()
    grade_validator = GradeValidator()
    students_service = StudentService(students_repo, students_validator)
    assignment_service = AssignmentService(assignment_repo, assignment_validator)
    grades_service = GradeService(students_repo, assignment_repo, students_service, assignment_service,
                                  grades_repo, grade_validator)

    UI = UserInterface(grades_service, assignment_service, students_service)
    UI.menu()

