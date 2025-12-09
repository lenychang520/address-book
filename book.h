#pragma once
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>

typedef struct Profile {
	char name[20];
	char sex[10];
	char phone[12];
	int age;//这里的age不要改成数组的形式，否则后续打印的时候会出bug
}Profile;

typedef struct Contact {
	Profile* date;
	int count;
	int capacity;
}Contact;


void Add(Contact* con);
void Initial(Contact* con);
void Display(const Contact* con);
void Del(Contact* con);
int find(const Contact* con, char name[20]);
void Find(const Contact* con);
void Modify(Contact* con);
void Sort(Contact* con);
int sort(const void* name1, const void* name2);
void Modify_capacity(Contact* con);//扩容
void Save(const Contact* con);//保存通讯录
