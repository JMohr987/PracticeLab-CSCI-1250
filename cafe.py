#!/usr/bin/env python3

def titleScreen(cafe, rate):
    print("--------------------")
    print(f"Welcome to {cafe}!\nThe tax rate is {rate}%.")
    print("--------------------\n")


def menu():
    print("--------------------")
    print("Menu:\n")
    print("(1) Add Item")
    print("(2) View Cart")
    print("(3) Remove item by number")
    print("(4) Checkout")
    print("(5) Quit")
    print("--------------------")
    userInput = 0
    while(True):
        userInput = input("Make your selection: ")
        if(userInput >= "1" and userInput <= "5" and len(userInput) == 1):
            return int(userInput)

        print("Invalid selection, try again!")
        print("--------------------")



def addItem(name, price, qty):
    newName = ""
    while(True):
        newName = input("Input item name: \n")
        newName = newName.strip()

        if(newName != ""):
            break

        print("Input a valid Name!")
    
    newPrice = 0
    while(True):
        newPrice = input("Input item price: \n")
        if(float(newPrice) >= 0):
            break

        print("Invalid item price!")

    newQty = 0

    while(True):
        newQty = input("Input item quantity: \n")
        if(int(newQty) >= 0):
            break

        print("Invalid item quantity!")

    name.append(newName)
    price.append(float(newPrice))
    qty.append(int(newQty))

def viewCart(name, price, qty):
    print("--------------------")
    for i in range(len(name)):
        print(f"Item: {name[i]}, total price: {price[i] * qty[i]}")

    print("--------------------")


def removeItemByNumber(name, price, qty):
    print("--------------------")
    for i in range(len(name)):
        print(f"{i + 1}: {name[i]}")

    removeIndex = int(input("Select item to be removed: "))

    name.pop(removeIndex - 1)
    price.pop(removeIndex - 1)
    qty.pop(removeIndex - 1)


def computeSubtotal(name, price, qty):
    totalPrice = 0.0

    for i in range(len(price)):
        totalPrice = (price[i] * qty[i]) + totalPrice

    print("Test subtotal: ", totalPrice)

    return totalPrice

def computeTax(subtotal, rate):
    return subtotal * (rate)

def applyDiscount(subtotal):
    inputCode = input("Input a discount code: ")

    if(inputCode == "STUDENT10"):
        return subtotal * 0.1

    return 0

def checkout(name, price, qty, rate):
    beforeTax = computeSubtotal(name, price, qty)
    tax = computeTax(beforeTax, rate)
    savings = applyDiscount(beforeTax + tax)
    finalTotal = beforeTax + tax - savings

    print("--------------------")
    print("--------------------")
    print("RECIPT: ")
    for i in range(len(name)):
        print(f"Item: {name[i]}\nQuantity: {qty[i]}")
        print(f"Unit Price: {price[i]}\nTotal Price: {price[i] * qty[i]}")
        print("--------------------")

    print(f"Subtotal: {beforeTax}")
    print(f"Tax: {tax}")
    print(f"Savings: {savings}")
    print(f"Final Price: {finalTotal}")
    print("Thank you for your purchase!")
    print("--------------------")
    print("--------------------")




def main():
    cafeName = "Starbucks"
    taxRate = 0.10

    nameList = ["Apple", "Orange", "Banana"]
    priceList = [2.0, 3.0, 1.0]
    quantityList = [1, 1, 1]

    selection = 0

    titleScreen(cafeName, taxRate)

    while(True):
        selection = menu()

        if(selection == 1):
            addItem(nameList, priceList, quantityList)

        elif(selection == 2):
            viewCart(nameList, priceList, quantityList)
            
        elif(selection == 3):
            removeItemByNumber(nameList, priceList, quantityList)

        elif(selection == 4):
            checkout(nameList, priceList, quantityList, taxRate)

        elif(selection == 5):
            print("Thanks for coming to the cafe! Bye!")
            break


main()
