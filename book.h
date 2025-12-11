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


void Add(Contact* con);//增加联系人
void Initial(Contact* con);//初始化通讯录
void Display(const Contact* con);//展示通讯录讯息
void Del(Contact* con);//删除联系人
int find(const Contact* con, char name[20]);//找到联系人的下标并返回
void Find(const Contact* con);//查找联系人
void Modify(Contact* con);//修改通讯录讯息
void Sort(Contact* con);//按姓名排序
int sort(const void* name1, const void* name2);//该函数是用于qsort的比较函数
void Modify_capacity(Contact* con);//扩容
void Save(const Contact* con);//保存通讯录
