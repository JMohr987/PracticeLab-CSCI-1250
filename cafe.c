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
    for(int i = 0; i < rows; ++i){
        printf("%s\n", menu[i]);
    }
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

void AddItem(List *itemList){
    Item *newItem = (Item *)malloc(sizeof(Item));
    GetItemName(&newItem);
    GetItemPrice(&newItem);
    itemList->push_back(itemList, newItem);
    for(Node *it = itemList->head; it != NULL; it = it->nextElement){ 
        printf("%s: $%.2f\n", 
            (((Item *)(it->element))->name), (((Item *)(it->element))->price));
    }
}

    

void ViewCart(List *itemList){
    for(Node *it = itemList->head; it != NULL; it = it->nextElement){ 
        printf("%s: $%.2f\n", 
            (((Item *)(it->element))->name), (((Item *)(it->element))->price));
    }
}

bool MenuSelection(List *itemList){
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
            printf("adding item\n");
            AddItem(itemList);
            break;
        case '2':
            printf("Viewing Cart!\n");
            ViewCart(itemList);
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


    while(MenuSelection(&itemList)){
        PrintMenu(menu, rows);
    }


    //printf("%s\n", itemArr->name);
    //free(itemArr->name);
    //free(itemArr);


    return 0;
}


