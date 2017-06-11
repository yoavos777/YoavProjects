num = int(raw_input("Please enter a positive number "))
secret = ""
while (num > 0):
    	secret = str(num % 2) + secret
        num = num / 2
print secret
