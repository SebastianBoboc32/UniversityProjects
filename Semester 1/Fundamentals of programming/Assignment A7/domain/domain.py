class ExpenseException(Exception):
    def __init__(self, message):
        self.__message = message

    @property
    def message(self):
        return self.__message


class Expense:

    def __init__(self, day: int, amount: int, type_of: str):
        #if day not in range(1, 32):
            #raise ValueError("Day should be between 1->31")
        self.__day = day
        self.__amount = amount
        self.__type_of = type_of

    @property
    def type_of(self):
        return self.__type_of

    @property
    def amount(self):
        return self.__amount

    @amount.setter
    def amount(self, amount_new):
        if type(amount_new) != int:
            raise TypeError("Type of amount should be int")
        self.__amount = amount_new

    @property
    def day(self):
        return self.__day

    def __str__(self):
        return str(self.day)+","+str(self.amount)+","+self.type_of


def test_expense():
    new_expense = Expense(26, 1000, "misc")
    assert new_expense.day == 26
    assert new_expense.amount == 1000
    assert new_expense.type_of == "misc"
    assert str(new_expense) == "26,1000,misc"

    new_expense.amount = 2000
    assert str(new_expense) == "26,2000,misc"

    try:
        new_expense.amount = "2000"
    except ExpenseException:
        assert True


if __name__ == "__main__":

    test_expense()
