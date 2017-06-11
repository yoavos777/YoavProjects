from bank import Bank
from bank_account import BankAccount

new_bank = Bank("shalom")
new_bank.new_account("yoav")
new_bank.new_account("dani")
new_bank.new_account("shira")
new_bank.delete_account("yoav")
new_bank.new_account("yoav")
print new_bank.get_account("shra")
