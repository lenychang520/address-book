#include "book.h"

enum choice {//用枚举来表示退、增、删、查、改、看、排、扩几大功能，方便后续的switch能清楚看清每个case的功能
	退出并保存,
	增加联系人,
	删除联系人,
	查找联系人,
	修改联系人,
	查看通讯录,
	通讯录排序,
	修改最大容量
};

void menu() {
	printf("***********************************************************\n");
	printf("***********1.增加联系人         2.删除联系人***************\n");
	printf("***********3.查找联系人         4.修改联系人***************\n");
	printf("***********5.查看通讯录         6.通讯录排序***************\n");
	printf("***********0.退出并保存         7.修改最大容量*************\n");
	printf("***********************************************************\n");
}

int main() {
	Contact con;
	//初始化通讯录
	Initial(&con);
	int input = 10;//不要初始化为0，防止一旦输入错误就直接退出程序
	do {
		menu();
		if (scanf("%d", &input) == 0) {
			printf("请输入正确的数字，而非字符\n");
			while (getchar() != '\n') {//清空缓存区
				;
			}
			continue;
		}
		switch (input) {
		case 增加联系人:
			if (con.count >= con.capacity) {//防止数组溢出，使联系人数量在通讯录的容量范围内
				printf("你最多只能存储%d个联系人，请删除部分联系人后再进行存储\n", con.capacity);
				continue;
			}
			Add(&con);
			break;
		case 删除联系人:
			if (con.count == 0) {
				printf("你的通讯录里没有一个联系人\n");
				continue;
			}
			Del(&con);
			break;
		case 查找联系人:
			if (con.count == 0) {
				printf("你的通讯录里没有一个联系人\n");
				continue;
			}
			Find(&con);
			break;		
		case 修改联系人:
			if (con.count == 0) {
				printf("你的通讯录里没有一个联系人\n");
				continue;
			}
			Modify(&con);
			break;
		case 查看通讯录:
			if (con.count == 0) {
				printf("你的通讯录里没有一个联系人\n");
				continue;
			}
			Display(&con);
			break;
		case 通讯录排序:
			if (con.count == 0) {
				printf("你的通讯录里没有一个联系人\n");
				continue;
			}
			Sort(&con);
			break;
		case 退出并保存:
			Save(&con);
			printf("正在退出\n");
			break;
		case 修改最大容量:
			Modify_capacity(&con);
		default:
			printf("请输入正确的对应数字\n");
			break;
		}
	} while (input);
	return 0;
}
