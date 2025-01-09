#include "dll.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Application specific data structures */
typedef struct person_{
    char name[32];
    int age;
    int weight;
} person_t;

typedef struct employee_ {
    char name[32];
    int employee_id;
    char designation[32];
    double salary;
} employee_t;

int search_person_by_name(void *data, void *key) {
    if(!data) return -1;
    person_t *person = (person_t*) data;
    char *name = (char *) key;
    if(strcmp(person->name, name) == 0) return 0;
    return -1;
}

int search_employee_by_id(void *data, void *key) {
    if(!data) return -1;
    employee_t *employee = (employee_t*)data;
    int employee_id = *(int*)key;
    if(employee->employee_id == employee_id) return 0;
    return -1;
}

static void print_person_details(person_t* person) {
    printf("Name = %s\n", person->name);
    printf("Age = %d\n", person->age);
    printf("Weight = %d\n", person->weight);
}

static void print_employee_details(employee_t *employee) {
    printf("Employee name: %s\n", employee->name);
    printf("Employee Id: %d\n", employee->employee_id);
    printf("Employee designation: %s\n", employee->designation);
    printf("Employee salary: %lf\n", employee->salary);
}

static void print_employee_db(dll_t *employee_db) {
    if(!employee_db || !employee_db->head) return;
    dll_node_t *head = employee_db->head;
    while(head) {
        print_employee_details(head->data);
        head = head->right;
    }
}

static void print_person_db(dll_t* person_db) {
    if(!person_db || !person_db->head) return;

    dll_node_t *head = person_db->head;
    person_t* data = NULL;

    while (head)
    {
        data = head->data;
        print_person_details(data);
        head = head->right;
    }
    
}

int main(int argc, char **argv) {
    person_t *person1 = calloc(1, sizeof(person_t));
    strncpy(person1->name, "Nitin", strlen("Nitin"));
    person1->age = 26;
    person1->weight = 61;
    person_t *person2 = calloc(1, sizeof(person_t));
    strncpy(person2->name, "Aadesh", strlen("Aadesh"));
    person2->age = 26;
    person2->weight = 65;
    person_t *person3 = calloc(1, sizeof(person_t));
    strncpy(person3->name, "Vijay", strlen("Vijay"));
    person3->age = 26;
    person3->weight = 59;

    /*Create a new linked list*/

    dll_t *person_db = get_new_dll();
    add_data_to_dll(person_db, person1);
    add_data_to_dll(person_db, person2);
    add_data_to_dll(person_db, person3);

    print_person_db(person_db);

    registerSearchCallback(person_db, search_person_by_name);
    char *searchName = "Nitin";
    person_t *searched_person = searchByKey(person_db, searchName);
    if(searched_person != NULL) {
        printf("Searched Person: \n");
        print_person_details(searched_person);
    }

    /* Employees */

    employee_t *employee1 = calloc(1, sizeof(employee_t));
    strncpy(employee1->name, "Nitin", strlen("Nitin"));
    employee1->employee_id = 1;
    employee1->salary = 100;
    strncpy(employee1->designation, "C/C++ developer", strlen("C/C++ developer"));

    employee_t *employee2 = calloc(1, sizeof(employee_t));
    strncpy(employee2->name, "Sam", strlen("Sam"));
    employee2->employee_id = 3;
    employee2->salary = 100;
    strncpy(employee2->designation, "C/C++ developer", strlen("C/C++ developer"));

    employee_t *employee3 = calloc(1, sizeof(employee_t));
    strncpy(employee3->name, "Jibin", strlen("Jibin"));
    employee3->employee_id = 2;
    employee3->salary = 100;
    strncpy(employee3->designation, "C/C++ developer", strlen("C/C++ developer"));

    dll_t *employee_db = get_new_dll();
    add_data_to_dll(employee_db, employee1);
    add_data_to_dll(employee_db, employee2);
    add_data_to_dll(employee_db, employee3);
    
    print_employee_db(employee_db);

    registerSearchCallback(employee_db, search_employee_by_id);
    int search_id = 1;
    employee_t *searched_employee = searchByKey(employee_db, &search_id);
    if(searched_employee != NULL) {
        printf("Searched employee: \n");
        print_employee_details(searched_employee);
    }
    return 0;
}