import os
from Tkinter import *
from bank import Bank
"""root = Tk()
for r in range(3):
    for c in range(4):
        Tkinter.Label(root, text='R%s/C%s'%(r,c),borderwidth=1 ).grid(row=r,column=c)"""


class BankWindow(object):
    def __init__(self, master):
        self._master = master
        self._master.title("Bank")

        """self._bank_name = Entry(master, text='bank name')
        self._bank_name.pack()
        self._create_bank_button = Button(master, text='create bank!', command=self.create_bank)
        self._create_bank_button.grid(row=0)
        self._create_bank_button.pack()
        self._text_box = Text(master)
        self._text_box.pack()"""

        self._new_account_name = Entry(master, text='account name')
        self._new_account_name.pack()
        self._new_account_name.place(bordermode=OUTSIDE, height=20, width=100, relx=0.035, rely=0.05)
        self._create_account_button = Button(master, text='create account!', command=self.create_account)
        self._create_account_button.pack()
        self._create_account_button.place(bordermode=OUTSIDE, height=20, width=100, relx=0.035, rely=0.115)
        self._text_box2 = Text(master)
        self._text_box2.pack()
        self._text_box2.place(bordermode=OUTSIDE, height=20, width=200, relx=0.035, rely=0.185)

        self._delete_account_name = Entry(master, text='delete account')
        self._delete_account_name.pack()
        self._delete_account_name.place(bordermode=OUTSIDE, height=20, width=100, relx=0.255, rely=0.05)
        self._delete_account_button = Button(master, text='delete account', command=self.delete_account)
        self._delete_account_button.pack()
        self._delete_account_button.place(bordermode=OUTSIDE, height=20, width=100, relx=0.255, rely=0.115)
        self._text_box3 = Text(master)
        self._text_box3.pack()
        self._text_box3.place(bordermode=OUTSIDE, height=20, width=200, relx=0.255, rely=0.185)

        self._all_account_button = Button(master, text='Show all the accounts in the bank', command=self.show_accounts)
        self._all_account_button.pack()
        self._all_account_button.place(bordermode=OUTSIDE, height=20, width=200, relx=0.475, rely=0.05)
        self._text_box4 = Text(master)
        self._text_box4.pack()
        self._text_box4.place(bordermode=OUTSIDE, height=500, width=590, relx=0.475, rely=0.115)

        self._open_account_window = Entry(master, text='open account')
        self._open_account_window.pack()
        self._open_account_window.place(bordermode=OUTSIDE, height=20, width=110, relx=0.147, rely=0.4)
        self._open_account_window_button = Button(master, text='see your account!', command=self.open_account_window)
        self._open_account_window_button.pack()
        self._open_account_window_button.place(bordermode=OUTSIDE, height=20, width=110, relx=0.147, rely=0.47)

        self._bank = Bank("yoav")

    """def create_bank(self):
        self._bank = Bank(self._bank_name.get())
        self._text_box.insert(END, 'Bank %s created!\n' % self._bank.get_name())"""

    def create_account(self):
        self._text_box2.delete('1.0', END)
        self._account = self._bank.new_account(self._new_account_name.get())
        self._text_box2.insert(END, 'Account %s created!\n' % self._account)

    def delete_account(self):
        self._text_box3.delete('1.0', END)
        self._account = self._bank.delete_account(self._delete_account_name.get())
        self._text_box3.insert(END, 'Account %s deleted\n' % self._account)

    def show_accounts(self):
        self._text_box4.delete('1.0', END)
        self._accounts = self._bank.display_all_accounts
        self._text_box4.insert(END, "%s\n" % self._accounts)

    def open_account_window(self):
        self.file = open(r"C:\Users\yoav\Dropbox\PycharmProjects\ATM\bank_account.pyc", "w+")
        self.file.close()


root = Tk()
bank_window = BankWindow(root)
root.mainloop()