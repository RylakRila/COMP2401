#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>


#define MAX_CHARS_IN_NAME   16
#define MAX_NUM_EMPLOYEES  100


// Structure representing a person's name
typedef struct name {
  char first[MAX_CHARS_IN_NAME + 1];
  char  last[MAX_CHARS_IN_NAME + 1];
} NameType;

// Structure representing an employee
typedef struct emp {
  unsigned int	id;
  NameType      name;
  unsigned int  salary;
} EmployeeType;

typedef struct listNode {
    void            *data;
    struct listNode *next;
} ListNodeType;

// A global linked list of employees
ListNodeType        *employeeList = NULL;

// Add an employee (with data emp) to the list with the given head
int addEmployee(ListNodeType **listHead, char *firstName, char *lastName, unsigned int id, unsigned int salary) {
    // Create and initialize the data for the list item
    EmployeeType *emp = malloc(sizeof(EmployeeType));
    if (emp == NULL) {
        printf("Out of memory Error\n");
        return -1;
    }
    strncpy(emp->name.first, firstName, MAX_CHARS_IN_NAME);
	emp->name.first[MAX_CHARS_IN_NAME] = '\0';
	
	strncpy(emp->name.last, lastName, MAX_CHARS_IN_NAME);
	emp->name.last[MAX_CHARS_IN_NAME] = '\0';

	emp->id = id;
	emp->salary = salary;

    // Create a new node to add to the list
    ListNodeType *newNode = malloc(sizeof(ListNodeType));
    if (newNode == NULL) {
        printf("Out of memory Error\n");
        return -1;
    }
    newNode->data = emp;
    newNode->next = NULL;
    
    if (*listHead == NULL)
        *listHead = newNode;
    else {
        // Add the node to the end of the list
        ListNodeType *currentNode = *listHead;
        while (currentNode->next != NULL)
            currentNode = currentNode->next;
        currentNode->next = newNode;
    }

    return 0;
}

// Remove the employee with the given id from the list with the given head
void removeEmployee(ListNodeType **listHead, unsigned int id) {
    ListNodeType  *currentNode = *listHead;
    ListNodeType  *prevNode = NULL;
    while (currentNode != NULL) {
        if (((EmployeeType *)currentNode->data)->id == id) {
            if (prevNode != NULL)
                prevNode->next = currentNode->next;
            else
                *listHead = currentNode->next;
            free(currentNode->data);
            free(currentNode);
            break;
        }
        prevNode = currentNode;
        currentNode = currentNode->next;
    }
}

//----------------------------------------------------------------------------------------------------------
// Print an employee in this format:  "010345 - Sue Perman ($80,350)"
//----------------------------------------------------------------------------------------------------------
void printEmployee(EmployeeType *emp) {
	printf("%06d - %s %s ($%'d)\n", emp->id, emp->name.first, emp->name.last, emp->salary);
}

// Print a Linked List of employees, given its head
void printEmployeeList(ListNodeType *listHead) {
    ListNodeType *currentNode = listHead;
    while (currentNode != NULL) {
        printEmployee(currentNode->data);
        currentNode = currentNode->next;
    }
}

void freeEmployeeList(ListNodeType *listHead) {
    ListNodeType *currentNode = listHead;
    while (currentNode != NULL) {
        ListNodeType *nextNode = currentNode->next;
        free(currentNode->data);
        free(currentNode);
        currentNode = nextNode;
    }
}

//----------------------------------------------------------------------------------------------------------
// This is where the fun begins
//----------------------------------------------------------------------------------------------------------
int main(void) {
    setlocale(LC_NUMERIC, ""); // This allows commas to be shown in the salary when printing
        
    addEmployee(&employeeList, "Sue",  "Perman",  10345, 80350);
    addEmployee(&employeeList, "Adam", "Aneeve",  12767, 78980);
    addEmployee(&employeeList, "Ming", "Vozz",    11890, 90320);
    addEmployee(&employeeList, "Hank", "Urchiff", 10528, 92450);
    addEmployee(&employeeList, "Jen",  "Tull",    11582, 82230);

    removeEmployee(&employeeList, 10528);
    removeEmployee(&employeeList, 10345);

    printf("Here is an array of employees: \n");
    printEmployeeList(employeeList);

    freeEmployeeList(employeeList);
}

