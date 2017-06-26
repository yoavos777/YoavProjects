from Tkinter import *

from bank_account import BankAccount


class BankAccountWindow(object):
    def __init__(self, master):
        self._master = master
        self._master.title("BankAccount")
        self._deposit_account_name = Entry(master, text='amount of money')
        self._deposit_account_name.pack()
        self._deposit_account_name.place(bordermode=OUTSIDE, height=20, width=200, relx=0.035, rely=0.05)
        self._deposit_button = Button(master, text='deposit money to your account', command=self.deposit)
        self._deposit_button.pack()
        self._deposit_button.place(bordermode=OUTSIDE, height=20, width=200, relx=0.035, rely=0.115)
        self._text_box = Text(master)
        self._text_box.pack()
        self._text_box.place(bordermode=OUTSIDE, height=20, width=200, relx=0.035, rely=0.185)

        self._withdraw_account_name = Entry(master, text='amount of money2')
        self._withdraw_account_name.pack()
        self._withdraw_account_name.place(bordermode=OUTSIDE, height=20, width=200, relx=0.365, rely=0.05)
        self._withdraw_button = Button(master, text='withdraw money from your account', command=self.withdraw)
        self._withdraw_button.pack()
        self._withdraw_button.place(bordermode=OUTSIDE, height=20, width=200, relx=0.365, rely=0.115)
        self._text_box2 = Text(master)
        self._text_box2.pack()
        self._text_box2.place(bordermode=OUTSIDE, height=20, width=200, relx=0.365, rely=0.185)

        self._get_name_button = Button(master, text='click here to see your name', command=self.get_name)
        self._get_name_button.pack()
        self._get_name_button.place(bordermode=OUTSIDE, height=20, width=200, relx=0.695, rely=0.05)
        self._text_box3 = Text(master)
        self._text_box3.pack()
        self._text_box3.place(bordermode=OUTSIDE, height=20, width=200, relx=0.695, rely=0.115)

        self._get_balance_button = Button(master, text='click here to see your balance', command=self.get_balance)
        self._get_balance_button.pack()
        self._get_balance_button.place(bordermode=OUTSIDE, height=20, width=200, relx=0.1925, rely=0.325)
        self._text_box4 = Text(master)
        self._text_box4.pack()
        self._text_box4.place(bordermode=OUTSIDE, height=20, width=200, relx=0.1925, rely=0.397)

        self._get_number_button = Button(master, text='click here to see your number')
        self._get_number_button.pack()
        self._get_number_button.place(bordermode=OUTSIDE, height=20, width=200, relx=0.53, rely=0.325)
        self._text_box5 = Text(master)
        self._text_box5.pack()
        self._text_box5.place(bordermode=OUTSIDE, height=20, width=200, relx=0.53, rely=0.397)

        self._new_account = BankAccount("yoav")

    def deposit(self):
        self._bank_account = self._new_account.deposit(int(self._deposit_account_name.get()))
        self._text_box.insert(END, "your deposit is %d \n" % self._bank_account)

    def withdraw(self):
        self._bank_account = self._new_account.withdraw(int(self._withdraw_account_name.get()))
        self._text_box2.insert(END, "your deposit is %d \n" % self._bank_account)

    def get_name(self):
        self._bank_account = self._new_account.get_name()
        self._text_box3.insert(END, "your name is %s \n" % self._bank_account)

    def get_balance(self):
        self._bank_account = self._new_account.get_balance()
        self._text_box4.insert(END, "your balance is %d \n" % self._bank_account)

root = Tk()
bank_account_window = BankAccountWindow(root)
root.mainloop()