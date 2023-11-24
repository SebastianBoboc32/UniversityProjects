from src.services.services import *


class UserInterfaceException(Exception):

    def __init__(self, message):
        self.__message = message

    @property
    def message(self):
        return self.__message


class UserInterface:

    def __init__(self, serv):
        self._service = serv

    def add(self, expense: Expense):
        self._service.add(expense)

    def display(self):
        for expense in self._service.return_all():
            print(str(expense))
        print("\n")

    def filter(self, param):
        self._service.filter(param)

    def undo(self):
        if self._service.operations == 0:
            raise ServiceException("Nothing to undo")
        self._service.undo()

    def menu(self):

        while True:
            print("1.Add a new expense")
            print("2.Display the list of expenses")
            print("3.Filter by a specified amount")
            print("4.Undo")
            print("0.Exit")
            print("\n")
            token = int(input("Select a command"))

            if token == 1:
                day = int(input("Choose the day of the expense: "))
                amount = int(input("Choose the amount of money spent"))
                type_of = input("Choose the type of the expense")
                if day not in range(1, 32):
                    raise UserInterfaceException("The input is not a day")
                self.add(Expense(day, amount, type_of))

            elif token == 2:
                self.display()

            elif token == 3:
                min_amount = int(input("Select the minimum amount for a expense to be kept"))
                self.filter(min_amount)

            elif token == 4:
                self.undo()

            elif token == 0:
                return
