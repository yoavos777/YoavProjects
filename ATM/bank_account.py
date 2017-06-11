import random


class BankAccount:
    def __init__(self, name):
        self._balance = 0
        self._account_number = random.randint(1, 1000)
        self._name = name

    def __str__(self):
        return "your balance is %d, your account number is %d and your name is %s" % (self._balance,
                                                                                      self._account_number, self._name)

    def __repr__(self):
        return "<balance : %d , account number : %d , name : %s>" % (self._balance, self._account_number, self._name)

    def deposit(self, amount):
        """
        deposit the amount of money that the user insert
        :param amount: the amount of money that the user want to deposit to the account.
        """
        self._balance += amount
        return self._balance

    def withdraw(self, amount):
        """

        :param amount: the amount of money that the user want to deposit to the account.
        """
        if amount > self._balance:
            raise ValueError("That's more than what you have!")
        else:
            self._balance -= amount
        return self._balance

    def get_name(self):
        return self._name

    def get_balance(self):
        return self._balance

    def get_account_number(self):
        print self._account_number








