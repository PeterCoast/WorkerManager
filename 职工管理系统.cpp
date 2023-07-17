#include<iostream>
#include"workerManager.h"
using namespace std;


int main()
{
	WorkerManager vm;
	char choice = '0';
	while (true) {
		vm.ShowMenu();
		cin >> choice;
		switch (choice)
		{
		case '1':  //1.增加职工信息
			vm.AddEmp();
			break;
		case '2':  //2.显示职工信息
			vm.showEmp();
			break;
		case '3':  //3.删除离职职工
			vm.delEmp();
			break;
		case '4':  //4.修改职工信息
			vm.modEmp();
			break;
		case '5':  //5.查找职工信息
			vm.findEmp();
			break;
		case '6':  //6.按照编号排序
			vm.sortEmp();
			break;
		case '7':  //7.清空所有信息
			vm.clearEmp();
			break;
		case '8':  //8.输出到csv表
			vm.showForm();
			break;
		case '0':  //0.退出管理系统
			vm.ExitSystem();
			break;
		default:
			cout << "输入错误！" << endl;
			system("pause");
			system("cls");
			break;
		}
	}

	system("pause");
	return 0;
}