#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>
#include "linked_list.h"
#define MAX_ITEM_LENGTH 50

typedef struct{
    char *name;
    double price;
    int quantity;
} Item;


bool IsNumber(char *number){
    bool decimal = false;
    for(int i = 0; i < strlen(number); ++i){
        if(isdigit(number[i])){
            ;
        }else if(number[i] == '.' && !decimal){
            decimal = true;
        }else{
            return false;
        }
    }
    
    return true;
}

void PrintBanner(char *name, double taxRate){
    printf("----------------------------------\n");
    printf("%s %s\n%s %f\n", "Welcome to:", name, "Tax rate:", taxRate);
    printf("----------------------------------\n");
}


void PrintMenu(char *menu[], int rows){
    printf("----------------------------------\n");
    for(int i = 0; i < rows; ++i){
        printf("%s\n", menu[i]);
    }
    printf("----------------------------------\n");
    printf("Make your selection: ");
}


void GetItemName(Item **newItem){
    char temp[MAX_ITEM_LENGTH];

    printf("Enter item name: ");

    fgets(temp, MAX_ITEM_LENGTH, stdin);

    temp[strcspn(temp, "\n")] = '\0';

    (*newItem)->name = (char *)malloc((strlen(temp) + 1) * sizeof(char));
    strcpy((*newItem)->name, temp);


    //printf("%s %ld\n", "Length of string:", strlen(newItem->name));
    //printf("%s %s\n", "String:", newItem->name);


}

void GetItemPrice(Item **newItem){
    char temp[MAX_ITEM_LENGTH];
    
    printf("Enter item price: ");

    while(true){
        fgets(temp, MAX_ITEM_LENGTH, stdin);
        temp[strcspn(temp, "\n")] = '\0';

        if(IsNumber(temp)){
            break;
        }
    }

    sscanf(temp, "%lf", &((*newItem)->price));

}

void GetItemQuantity(Item **newItem){
    char temp[MAX_ITEM_LENGTH];
    
    printf("Enter item quantity: ");

    while(true){
        fgets(temp, MAX_ITEM_LENGTH, stdin);
        temp[strcspn(temp, "\n")] = '\0';

        if(IsNumber(temp)){
            break;
        }
    }

    sscanf(temp, "%d", &((*newItem)->quantity));

}

void AddItem(List *itemList){
    Item *newItem = (Item *)malloc(sizeof(Item));
    GetItemName(&newItem);
    GetItemPrice(&newItem);
    GetItemQuantity(&newItem);
    itemList->push_back(itemList, newItem);
    //for(Node *it = itemList->head; it != NULL; it = it->nextElement){ 
    //    printf("%s: $%.2f\n", 
    //        (((Item *)(it->element))->name), (((Item *)(it->element))->price));
    //}
}

void DeleteItem(List *itemList){
    char temp[MAX_ITEM_LENGTH];
    int i = 1;

    for(Node *it = itemList->head; it != NULL; it = it->nextElement){
        printf("%d: %s\n",
            i,
            (((Item *)(it->element))->name));
        ++i;
    }

    printf("Enter an index to delete an item\n");

    while(true){
        fgets(temp, MAX_ITEM_LENGTH, stdin);
        temp[strcspn(temp, "\n")] = '\0';

        if(IsNumber(temp)){
            break;
        }
    }
    sscanf(temp, "%d", &i);
    itemList->pop(itemList, i);

}

double ComputeSubtotal(List *itemList){
    double totalPrice = 0.0;

    for(Node *it = itemList->head; it != NULL; it = it->nextElement){
        totalPrice += ((Item *)(it->element))->price * ((Item *)(it->element))->quantity;
    }

    return totalPrice;
}

double ComputeTax(double subtotal, double rate){
    return subtotal * rate;
}

double ApplyDiscount(double subtotal){
    printf("Enter discount code: ");
    char temp[MAX_ITEM_LENGTH];

    fgets(temp, MAX_ITEM_LENGTH, stdin);
    temp[strcspn(temp, "\n")] = '\0';

    if(!strcmp(temp, "STUDENT10")){
        return subtotal * 0.1;
    }

    return 0;
}

void Checkout(List *itemList, double taxRate){
    double beforeTax = ComputeSubtotal(itemList); 
    double tax = ComputeTax(beforeTax, taxRate);
    double savings = ApplyDiscount(beforeTax + tax);
    double finalTotal = beforeTax + tax - savings;

    printf("----------------------------------\n");
    printf("----------------------------------\n");
    printf("RECIEPT\n");
    for(Node *it = itemList->head; it != NULL; it = it->nextElement){ 
        printf("Item: %s\n", 
            (((Item *)(it->element))->name));
        printf("Quantity: %d\n", 
            (((Item *)(it->element))->quantity));
        printf("Unit Price: %.2f\n", 
            (((Item *)(it->element))->price));
    }
    printf("----------------------------------\n");
    printf("Subtotal: %.2f\n", beforeTax);
    printf("Tax: %.2f\n", tax);
    printf("Savings: %.2f\n", savings);
    printf("Final Total: %.2f\n", finalTotal);
    printf("Thank you for your purchase!\n");
    printf("----------------------------------\n");
    printf("----------------------------------\n");
}

void ViewCart(List *itemList){
    for(Node *it = itemList->head; it != NULL; it = it->nextElement){ 
        printf("%s: $%.2f, x%d\n", 
            (((Item *)(it->element))->name),
            (((Item *)(it->element))->price),
            (((Item *)(it->element))->quantity));
    }
}

bool MenuSelection(List *itemList, double taxRate){
    char selection[6];
    
    while(true){
        fgets(selection, 6, stdin);

        bool clearStdIn = true;
        for(int i = 0; i < sizeof(selection); ++i){
            if(selection[i] == '\n'){
                clearStdIn = false;
                break;
            }
        }

        if(clearStdIn){
            while(getchar() != '\n');
        }

        selection[strcspn(selection, "\n")] = '\0';

        if(strlen(selection) > 1){
            printf("Input too long! Only use numbers 1 - 5!\n");
            continue;
        }

        if(*selection < '1' || *selection > '5'){
            printf("Input only numbers 1 - 5!\n");
            continue;
        }

        break;
    }

    switch(*selection){
        case '1':
            AddItem(itemList);
            break;
        case '2':
            ViewCart(itemList);
            break; 
        case '3':
            DeleteItem(itemList);
            break;
        case '4':
            Checkout(itemList, taxRate);
            break;
        case '5':
            printf("Thanks for visiting our cafe!\n");
            return false;
        default:
            break;
    }
    return true;
}

int main(int argc, char **argv){
    List itemList = {NULL, NULL, 0, &push_back, &push_front, &pop, &cleanup};
    char cafeName[] = {"Jackie Cafe"};
    double taxRate = 0.10;
    int rows = 5;

    char *menu[] = {"1: Add items", "2: View Cart", "3: Remove Item", "4: Checkout", "5: Quit"};   


    PrintBanner(cafeName, taxRate);
    PrintMenu(menu, rows);


    while(MenuSelection(&itemList, taxRate)){
        PrintMenu(menu, rows);
    }


    //printf("%s\n", itemArr->name);
    //free(itemArr->name);
    //free(itemArr);


    return 0;
}


