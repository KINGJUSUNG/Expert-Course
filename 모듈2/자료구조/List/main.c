#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"


typedef struct Person {
	char name[32];
	int age;
	Node list;
}Person;


const char* printPerson(void* node) {
    static char buf[64] = { 0, };
    Person* p = list_entry(node, Person, list);
    sprintf(buf, "%s(%d)", p->name, p->age);
    return (const char*)buf;
}


int main(void) {
    
    LIST_HEAD(head);

	Person persons[5] = {
        {"a", 10},
		{"b", 20},
		{"c", 30},
		{"d", 40},
		{"e", 50}
	};

	for (int i = 0; i < 5; i++) {
		listAdd(&head, &(persons[i].list));

        listDisplay(&head, printPerson);
        listDisplayBackwardly(&head, printPerson);

		system("pause");
		system("cls");
    }

	listDisplay(&head, printPerson);

	return 0;
}

