import bank_account


class Bank:
    def __init__(self, name):
        self._name = name
        self._accounts = list()

    def __str__(self):
        return "The name of the bank is %s, and it has %d accounts" % (self._name, len(self._accounts))

    def __repr__(self):
        represent = ""
        represent += "< name : %s , accounts : %d >\n" % (self._name, len(self._accounts))
        for account in self._accounts:
            represent += repr(account) + "\n"
        return represent

    def new_account(self, name):
        """
        Adds a new bank account to the bank.
        :param name: The name of the new bank account.
        """
        for account in self._accounts:
            if account.get_name() == name:
                raise ValueError("This name is already exist")
        self._accounts.append(bank_account.BankAccount(name))
        return name

    def delete_account(self, name):
        """
        Delete an account
        :param name: The name of the bank account.
        """
        for account in self._accounts:
            if name == account.get_name():
                self._accounts.remove(account)
        return name

    def display_all_accounts(self):
        """
        Represent all the accounts in the bank.
        """
        for account in self._accounts:
            print(account)
            return account

    def get_account(self, name):
        """
        :param name: The name of the bank account that the user want to see.
        :return: the account that the user want to see.
        """
        for account in self._accounts:
            if name == account.get_name():
                return account
        raise NameError("There is no such account")

    def get_name(self):
        return self._name