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
		case '1':  //1.����ְ����Ϣ
			vm.AddEmp();
			break;
		case '2':  //2.��ʾְ����Ϣ
			vm.showEmp();
			break;
		case '3':  //3.ɾ����ְְ��
			vm.delEmp();
			break;
		case '4':  //4.�޸�ְ����Ϣ
			vm.modEmp();
			break;
		case '5':  //5.����ְ����Ϣ
			vm.findEmp();
			break;
		case '6':  //6.���ձ������
			vm.sortEmp();
			break;
		case '7':  //7.���������Ϣ
			vm.clearEmp();
			break;
		case '8':  //8.�����csv��
			vm.showForm();
			break;
		case '0':  //0.�˳�����ϵͳ
			vm.ExitSystem();
			break;
		default:
			cout << "�������" << endl;
			system("pause");
			system("cls");
			break;
		}
	}

	system("pause");
	return 0;
}