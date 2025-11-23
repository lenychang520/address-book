#include "book.h"
//增、删、查、改、看、排、退
enum choice
{
	退出通讯录,
	增加联系人,
	删除联系人,
	查找联系人,
	修改联系人,
	查看通讯录,
	通讯录排序
};

void menu()
{
	printf("***********************************************************\n");
	printf("***********1.增加联系人         2.删除联系人***************\n");
	printf("***********3.查找联系人         4.修改联系人***************\n");
	printf("***********5.查看通讯录         6.通讯录排序***************\n");
	printf("***********0.退出通讯录************************************\n");
	printf("***********************************************************\n");
}

int main()
{
	Contact con;
	//初始化通讯录
	Initial(&con);
	int input = 0;
	do
	{

		menu();
		scanf("%d", &input);
		switch (input)
		{
		case 增加联系人:
			if (con.count > 100)//防止数组溢出
			{
				printf("你最多只能存储100个联系人，请删除部分联系人后再进行存储\n");
			}
			Add(&con);
			break;
		case 删除联系人:
			if (con.count == 0)
			{
				printf("你的通讯录里没有一个联系人\n");
			}
			Del(&con);
			break;
		case 查找联系人:
			if (con.count == 0)
			{
				printf("你的通讯录里没有一个联系人\n");
			}
			Find(&con);
			break;		
		case 修改联系人:
			if (con.count == 0)
			{
				printf("你的通讯录里没有一个联系人\n");
			}
			Modify(&con);
			break;
		case 查看通讯录:
			if (con.count == 0)
			{
				printf("你的通讯录里没有一个联系人\n");
			}
			Display(&con);
			break;
		case 通讯录排序:
			if (con.count == 0)
			{
				printf("你的通讯录里没有一个联系人\n");
			}
			Sort(&con);
			break;
		case 退出通讯录:
			printf("正在退出\n");
			break;
		default:
			printf("请输入正确的对应数字\n");
			break;
		}
	} while (input);
	return 0;
}