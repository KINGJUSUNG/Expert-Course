#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "array.h"


// 사용자 정의 데이터타입
typedef struct Person {
	char *name;
	int age;
}Person;

// 사용자 정의 함수
void freePerson(void* person) {
	if (person == NULL) {
		return NULL;
	}
	Person* p = (Person*)person;
	free(p->name);
	free(p);
}

// 사용자 정의 함수
const char* displayPerson(const void* person) {
	static char buf[32];
	Person* p = (Person*)person;
	sprintf(buf, "%s(%d)", p->name, p->age);
	return (const char*)buf;
}


int main(void) {

	char *names[5] = { "a", "b", "c", "d", "e" };
	Person** p2 = malloc(sizeof(Person*) * 5);
	for (int i = 0; i < 5; i++) {
		p2[i] = malloc(sizeof(Person));
		p2[i]->name = malloc(sizeof(char) * 32);
		strcpy(p2[i]->name, names[i]);
		p2[i]->age = i + 1;
	}

	Array* arr = arrayCreate(freePerson);

	for (int i = 0; i < 5; i++) {
		arrayAdd(arr, p2[i]);
		arrayDisplay(arr, displayPerson);
	}

	arrayDestroy(arr);
	return 0;
}