#include "book.h"

int find(const Contact* con, char name[20]) {//找到联系人的下标并返回
	assert(con);
	int i = 0;
	for (i = 0; i < con->count; i++) {
		if (0 == strcmp(con->date[i].name, name)) {
			return i;
		}
	}
	return -1;
}

void Add(Contact* con) {
	assert(con);
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
	assert(con);
	FILE* rf = fopen("list.txt", "rb");
	if (rf == NULL) {
		perror("fopen");
	}
	con->capacity = 100;
	con->count = 0;
	con->date = (Profile*)calloc(100, sizeof(Profile));
	if (fscanf(rf, "%d %d", &con->count, &con->capacity) != 2) {
		fclose(rf);
		rf = NULL;
		return;
	}
	else {
		int i = 0;
		for (i = 0; i < con->count; i++) {
			fscanf(rf, "%s %s %s %d", con->date[i].name, con->date[i].sex, con->date[i].phone, &con->date[i].age);
		}
	}
	fclose(rf);
	rf = NULL;
	return;
}

void Display(const Contact* con) {
	assert(con);
	int i = 0;
	printf("%-20s\t%-10s\t%-12s\t%-s\n", "姓名", "性别", "手机号", "年龄");
	for (i = 0; i < con->count; i++) {
		printf("%-20s\t%-10s\t%-12s\t%-d\n", con->date[i].name, con->date[i].sex, con->date[i].phone, con->date[i].age);
	}
	return;
}

void Del(Contact* con) {
	assert(con);
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
	assert(con);
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
	qsort(con->date, con->count, sizeof(con->date[0]), sort);
	printf("排序成功\n");
	return;
}

void Modify_capacity(Contact* con) {
	printf("现在的通讯录容量为%d，请输入改变后的通讯录容量：\n", con->capacity);
	int input = 0;
	scanf("%d", &input);
	con->capacity = input;
	Profile* p = realloc(con->date, input * sizeof(Profile));
	con->date = p;
	printf("修改成功\n");
	return;
}

void Save(const Contact* con) {
	FILE* pfwrt = fopen("list.txt", "wb");
	if (pfwrt == NULL) {
		perror("fopen");
	}
	int i = 0;
	fprintf(pfwrt, "%d %d\n", con->count, con->capacity);
	for (i = 0; i < con->count; i++) {
		fprintf(pfwrt, "%s %s %s %d\n", con->date[i].name, con->date[i].sex, con->date[i].phone, con->date[i].age);
	}
	fclose(pfwrt);
	pfwrt = NULL;
	return;
}
