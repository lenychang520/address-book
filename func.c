#include "book.h"

int find(const Contact* con, char name[20]) {//找到联系人的下标并返回
	assert(con);//防止空指针，若为空直接程序报错，主要用于提示程序员。
	int i = 0;
	for (i = 0; i < con->count; i++) {
		if (0 == strcmp(con->date[i].name, name)) {
			return i;
		}
	}
	return -1;
}

void Add(Contact* con) {
	assert(con);//防止空指针，若为空直接程序报错，主要用于提示程序员。
	printf("请输入联系人的姓名\n");
	scanf("%20s", con->date[con->count].name);
	printf("请输入联系人的性别\n");
	scanf("%10s", con->date[con->count].sex);
	printf("请输入联系人的号码\n");
	scanf("%12s", con->date[con->count].phone);
	printf("请输入联系人的年龄\n");
	scanf("%d", &con->date[con->count].age);
	con->count++;//使得每次增加的次数都能步进
	printf("增加成功\n");
	return;
}

void Initial(Contact* con) {
	assert(con);//防止空指针，若为空直接程序报错，主要用于提示程序员。
	FILE* rf = fopen("list.txt", "rb");
	if (rf == NULL) {//防御性检验，检查文件是否存在，不存在的话就默认初始化
		con->capacity = 100;
		con->count = 0;
		con->date = (Profile*)calloc(100, sizeof(Profile));//如果文件打开失败，就创建一个新文件
		if (con->date == NULL) {//如果内存不够，就报错
			perror("内存分配失败");
			exit(1);//如果没有通讯录文件，还创建不了，那就立即终止程序的运行。
		}
		return;
	}
	else {
		fscanf(rf, "%d %d", &con->count, &con->capacity);//若原先存在通讯录，则将通讯录的容量和联系人数拷贝一下
		int i = 0;
		Profile* p = calloc(con->capacity, sizeof(Profile));
		if (p == NULL) {
			perror("内存分配失败");
			exit(1);
		}
		con->date = p;//分配空间
		for (i = 0; i < con->count; i++) {
			fscanf(rf, "%s %s %s %d", con->date[i].name, con->date[i].sex, con->date[i].phone, &con->date[i].age);//将原先的的通讯录里的信息拷贝一下。
		}
	}
	fclose(rf);
	rf = NULL;
	return;
}

void Display(const Contact* con) {
	assert(con);//防止空指针，若为空直接程序报错，主要用于提示程序员。
	int i = 0;
	printf("%-20s\t%-10s\t%-12s\t%-s\n", "姓名", "性别", "手机号", "年龄");
	for (i = 0; i < con->count; i++) {
		printf("%-20s\t%-10s\t%-12s\t%-d\n", con->date[i].name, con->date[i].sex, con->date[i].phone, con->date[i].age);
	}
	return;
}

void Del(Contact* con) {
	assert(con);//防止空指针，若为空直接程序报错，主要用于提示程序员。
	char name[20] = { 0 };
	printf("请输入你想要删除的联系人的姓名\n");
	scanf("%20s", name);
	int ret = find(con, name);
	if (ret != -1) {
		int i = 0;
		for (i = ret; i < con->count - 1; i++) {//将后续的数据全部往前移
			con->date[i] = con->date[i + 1];
		}
		memset(&con->date[con->count - 1], 0, sizeof(con->date[con->count]));//将最后的一个旧数组清空
		con->count--;
		printf("删除成功\n");
	}
	else {
		printf("不存在这么一个联系人\n");
	}
	return;
}

void Find(const Contact* con) {//更类似于查看联系人
	assert(con);//防止空指针，若为空直接程序报错，主要用于提示程序员。
	char name[20] = { 0 };
	printf("请输入你要查找的联系人的姓名\n");
	scanf("%20s", name);
	int ret = find(con, name);
	if (ret != -1) {
		printf("%-20s\t%-10s\t%-12s\t%-s\n", "姓名", "性别", "手机号", "年龄");
		printf("%-20s\t%-10s\t%-12s\t%-d\n", con->date[ret].name, con->date[ret].sex, con->date[ret].phone, con->date[ret].age);
	}
	else {
		printf("该联系人不存在\n");
	}
	return;
}

void Modify(Contact* con) {
	char name[20] = { 0 };
	printf("请输入你要修改的联系人姓名\n");
	scanf("%20s", name);
	int ret = find(con, name);
	if (ret != -1) {
		printf("以下是该联系人的信息\n");
		printf("%-20s\t%-10s\t%-12s\t%-s\n", "姓名", "性别", "手机号", "年龄");
		printf("%-20s\t%-10s\t%-12s\t%-d\n", con->date[ret].name, con->date[ret].sex, con->date[ret].phone, con->date[ret].age);
		printf("请输入修改后联系人的姓名\n");
		scanf("%20s", con->date[ret].name);
		printf("请输入修改后联系人的性别\n");
		scanf("%10s", con->date[ret].sex);
		printf("请输入修改后联系人的号码\n");
		scanf("%12s", con->date[ret].phone);
		printf("请输入修改后联系人的年龄\n");
		scanf("%d", &con->date[ret].age);
		printf("修改成功\n");
		printf("%-20s\t%-10s\t%-12s\t%-s\n", "姓名", "性别", "手机号", "年龄");
		printf("%-20s\t%-10s\t%-12s\t%-d\n", con->date[ret].name, con->date[ret].sex, con->date[ret].phone, con->date[ret].age);
	}
	else {
		printf("该联系人不存在\n");
	}
	return;
}

int sort(const void* name1, const void* name2) {//接收到的是Profile结构体指针，名为name1和name2。
	return strcmp(((const Profile*)name1)->name, ((const Profile*)name2)->name);//因此把它从void指针转化成Profile结构体指针
}

void Sort(Contact* con) {
	qsort(con->date, con->count, sizeof(con->date[0]), sort);//快排函数，在库函数<stdlib.h>中
	printf("排序成功\n");
	return;
}

void Modify_capacity(Contact* con) {
	printf("现在的通讯录容量为%d，联系人的数量为%d，请输入改变后的通讯录容量：\n", con->capacity, con->count);
	int input = 0;
	while (1) {
		scanf("%d", &input);
		if (input >= con->count) {//只要输入的数字“合法”，则进行修改
			Profile* p = realloc(con->date, input * sizeof(Profile));//重新分配动态内存
			if (p == NULL) {//防止内存不够用来分配
				printf("没有足够多的内存供分配，请重新分配合理的大小\n");
				continue;
			}
			con->capacity = input;
			con->date = p;
			printf("修改成功\n");
			break;
		}
		else {//防御性编程
			printf("修改后的容量不能小于现有的联系人数，请重新输入\n");
			continue;
		}
	}
	return;
}

void Save(const Contact* con) {
	FILE* pfwrt = fopen("list.txt", "wb");//以二进制的形式写入文件内
	if (pfwrt == NULL) {//防御性检验，检查是否能正常打开
		perror("fopen");//将错误码转换成文字，并输出。
	}
	int i = 0;
	fprintf(pfwrt, "%d %d\n", con->count, con->capacity);//将通讯录的联系人数和通讯录的容量存到文件里
	for (i = 0; i < con->count; i++) {
		fprintf(pfwrt, "%s %s %s %d\n", con->date[i].name, con->date[i].sex, con->date[i].phone, con->date[i].age);//将联系人的具体信息存到文件里
	}
	fclose(pfwrt);
	pfwrt = NULL;//将悬空指针化空指针
	return;
}
