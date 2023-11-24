from src.repositories.memory_repo import MemoryRepo
from src.repositories.binary_file_repo import BinaryFileRepo
from src.repositories.text_file_repo import TextFileRepo
from src.services.services import ExpenseService
from src.ui.ui import UserInterface


if __name__ == "__main__":
    method = input("Select the repo implementation")
    if method not in ["text", "memory", "binary"]:
        raise ValueError("Invalid implementation method")

    elif method == "text":
        repository = TextFileRepo("expenses.txt")

    elif method == "binary":
        repository = BinaryFileRepo("expenses.bin")

    else:
        repository = MemoryRepo()

    for _ in range(10):
        repository.add_rand()
    services = ExpenseService(repository)
    UI = UserInterface(services)

    UI.menu()
