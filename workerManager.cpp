#include "workerManager.h"
WorkerManager::WorkerManager()
{
	system("mkdir data");
	system("cls");
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	if (!ifs.is_open())
	{
		//文件打开失败
		this->m_EmpNum = 0;
		this->m_EmpArray = NULL;
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		//文件存在 但为空
		this->m_EmpNum = 0;
		this->m_EmpArray = NULL;
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}

	//文件存在 并且有记录内容
	int num = this->getEmpNum();
	this->m_EmpNum = num;
	this->m_EmpArray = new Worker * [this->m_EmpNum];
	this->initEmp();
}

WorkerManager::~WorkerManager()
{
	if (this->m_EmpArray != NULL)
	{
		delete[] this->m_EmpArray;
		this->m_EmpArray = NULL;
	}
}

void WorkerManager::ShowMenu()
{
	cout << "************************************" << endl;
	cout << "******  欢迎使用职工管理系统 *******" << endl;
	cout << "*********  1.增加职工信息  *********" << endl;
	cout << "*********  2.显示职工信息  *********" << endl;
	cout << "*********  3.删除离职职工  *********" << endl;
	cout << "*********  4.修改职工信息  *********" << endl;
	cout << "*********  5.查找职工信息  *********" << endl;
	cout << "*********  6.按照编号排序  *********" << endl;
	cout << "*********  7.清空所有信息  *********" << endl;
	cout << "*********  8.输出到表格中  *********" << endl;
	cout << "*********  0.退出管理系统  *********" << endl;
	cout << "************************************" << endl;
	cout << endl << "请输入您的选择：";
}

void WorkerManager::ExitSystem()
{
	cout << "欢迎下次使用" << endl;
	system("pause");
	exit(0);
}

void WorkerManager::AddEmp()
{
	cout << "请输入添加职工数量" << endl;
	int addNum = 0;
	cin >> addNum;
	if (addNum > 0)
	{
		int newSize = this->m_EmpNum + addNum; //新空间人数

		Worker** newSpace = new Worker * [newSize];

		//把旧数据拷贝到新空间内
		if (this->m_EmpArray != NULL)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				newSpace[i] = this->m_EmpArray[i];
			}
		}

		//批量添加新数据
		for (int i = 0; i < addNum; i++)
		{
			int id; //职工编号
			string name; //职工姓名
			char dSelect; //部门选择

			cout << "请输入第" << i + 1 << "个新职工编号" << endl;
			cin >> id;

			cout << "请输入第" << i + 1 << "个新职工姓名" << endl;
			cin >> name;

			cout << "请选择该职工岗位：" << endl;
			cout << "1.普通职工" << endl;
			cout << "2.经理" << endl;
			cout << "3.老板" << endl;
			cin >> dSelect;
			while (dSelect < '1' || dSelect > '3')
			{
				cout << "输入有误！" << endl;
				cout << "请选择该职工岗位：" << endl;
				cout << "1.普通职工" << endl;
				cout << "2.经理" << endl;
				cout << "3.老板" << endl;
				cin >> dSelect;
			}
			Worker* worker = NULL;
			switch (dSelect)
			{
			case '1':
				worker = new Employee(id, name, 1);
				break;
			case '2':
				worker = new Manager(id, name, 2);
				break;
			case '3':
				worker = new Boss(id, name, 3);
				break;
			default:
				break;
			}
			newSpace[this->m_EmpNum + i] = worker;
		}
		delete[] this->m_EmpArray;
		this->m_EmpArray = newSpace;
		this->m_EmpNum = newSize;
		this->m_FileIsEmpty = false;

		cout << "成功添加" << addNum << "名新职工" << endl;
		this->save();
	}
	else
	{
		cout << "输入数据有误！" << endl;
	}
	system("pause");
	system("cls");
}

void WorkerManager::save()
{
	ofstream ofs;
	ofs.open(FILENAME, ios::out);
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		ofs << this->m_EmpArray[i]->m_Id << " "
			<< this->m_EmpArray[i]->m_Name << " "
			<< this->m_EmpArray[i]->m_DeptId << endl;
	}
	ofs.close();
}

int WorkerManager::getEmpNum()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	string buffer;
	int num = 0;
	while (getline(ifs, buffer))
	{
		num++;
	}
	ifs.close();
	return num;
}

void WorkerManager::initEmp()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	char id;
	string name;
	char dId;

	int index = 0;
	while (ifs >> id && ifs >> name && ifs >> dId)
	{
		Worker* worker = NULL;
		if (int(dId - 48) == 1) //普通员工
		{
			worker = new Employee(int(id - 48), name, int(dId - 48));
		}
		else if (int(dId - 48) == 2) //经理
		{
			worker = new Manager(int(id - 48), name, int(dId - 48));
		}
		else //老板
		{
			worker = new Boss(int(id - 48), name, int(dId - 48));
		}
		this->m_EmpArray[index++] = worker;

	}
	ifs.close();
}

void WorkerManager::showEmp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "记录不存在或为空" << endl;
	}
	else
	{
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			this->m_EmpArray[i]->showInfo();
		}
	}
	system("pause");
	system("cls");
}
void WorkerManager::delEmp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "记录不存在或为空" << endl;
	}
	else
	{
		cout << "请输入要删除的职工编号" << endl;
		int id = 0;
		cin >> id;
		int ret = this->isExist(id);
		if (ret != -1)
		{
			delete this->m_EmpArray[ret];
			this->m_EmpArray[ret] = NULL;
			for (int i = ret; i < this->m_EmpNum - 1; i++)
			{
				this->m_EmpArray[i] = this->m_EmpArray[i + 1];
			}
			this->m_EmpArray[this->m_EmpNum--] = NULL;
			this->save();
			cout << "删除成功" << endl;
		}
		else
		{
			cout << "查无此人" << endl;
		}
	}
	system("pause");
	system("cls");
}
int WorkerManager::isExist(int id)
{
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		if (this->m_EmpArray[i]->m_Id == id)
		{
			return i;
		}
	}
	return -1;
}
void WorkerManager::modEmp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "记录不存在或为空" << endl;
	}
	else
	{
		cout << "请输入要修改的职工编号" << endl;
		int id = 0;
		cin >> id;
		int ret = this->isExist(id);
		if (ret != -1)
		{
			int id; //职工编号
			string name; //职工姓名
			char dSelect; //部门选择

			cout << "请输入职工编号" << endl;
			cin >> id;

			cout << "请输入职工姓名" << endl;
			cin >> name;

			cout << "请选择该职工岗位：" << endl;
			cout << "1.普通职工" << endl;
			cout << "2.经理" << endl;
			cout << "3.老板" << endl;
			cin >> dSelect;
			while (dSelect < '1' || dSelect > '3')
			{
				cout << "输入有误！" << endl;
				cout << "请选择该职工岗位：" << endl;
				cout << "1.普通职工" << endl;
				cout << "2.经理" << endl;
				cout << "3.老板" << endl;
				cin >> dSelect;
			}
			Worker* worker = NULL;
			switch (dSelect)
			{
			case '1':
				worker = new Employee(id, name, 1);
				break;
			case '2':
				worker = new Manager(id, name, 2);
				break;
			case '3':
				worker = new Boss(id, name, 3);
				break;
			}
			delete this->m_EmpArray[ret];
			this->m_EmpArray[ret] = worker;
			this->save();
			cout << "修改成功" << endl;
		}
		else
		{
			cout << "查无此人" << endl;
		}
	}
	system("pause");
	system("cls");
}
void WorkerManager::findEmp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "记录不存在或为空" << endl;
	}
	else
	{
		cout << "请选择查找方式：" << endl;
		cout << "1.按照职工编号" << endl;
		cout << "2.按照职工姓名" << endl;
		char select;
		cin >> select;
		while (select < '1' || select>'2')
		{
			cout << "输入有误！" << endl;
			cout << "请选择查找方式：" << endl;
			cout << "1.按照职工编号" << endl;
			cout << "2.按照职工姓名" << endl;
			cin >> select;
		}
		if (select == '1') {
			cout << "请输入要查找的职工编号" << endl;
			int id = 0;
			cin >> id;
			int ret = this->isExist(id);
			if (ret != -1)
			{
				cout << "查找成功：" << endl;
				this->m_EmpArray[ret]->showInfo();
			}
			else
			{
				cout << "查无此人" << endl;
			}
		}
		else
		{
			cout << "请输入要查找的职工姓名" << endl;
			string name = "";
			bool flag = true;
			cin >> name;
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				if (this->m_EmpArray[i]->m_Name == name)
				{
					flag = false;
					this->m_EmpArray[i]->showInfo();
				}
			}
			if (flag)
			{
				cout << "查无此人" << endl;
			}
		}
	}
	system("pause");
	system("cls");
}
void WorkerManager::sortEmp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "记录不存在或为空" << endl;
	}
	else
	{
		cout << "请选择排序方式" << endl;
		cout << "1.按照职工编号升序" << endl;
		cout << "2.按照职工编号降序" << endl;
		char select;
		cin >> select;
		while (select < '1' || select>'2')
		{
			cout << "输入有误！" << endl;
			cout << "请选择排序方式" << endl;
			cout << "1.按照职工编号升序" << endl;
			cout << "2.按照职工编号降序" << endl;
			cin >> select;
		}
		Worker* worker = NULL;

		for (int i = 0; i < this->m_EmpNum - 1; i++)
		{
			for (int j = i + 1; j < this->m_EmpNum; j++)
			{
				if (select == '1')
				{
					if (this->m_EmpArray[i]->m_Id > this->m_EmpArray[j]->m_Id)
					{
						worker = this->m_EmpArray[i];
						this->m_EmpArray[i] = this->m_EmpArray[j];
						this->m_EmpArray[j] = worker;
						worker = NULL;
					}
				}
				else
				{
					if (this->m_EmpArray[i]->m_Id < this->m_EmpArray[j]->m_Id)
					{
						worker = this->m_EmpArray[i];
						this->m_EmpArray[i] = this->m_EmpArray[j];
						this->m_EmpArray[j] = worker;
						worker = NULL;
					}
				}
			}
		}
		this->save();
		cout << "排序完毕" << endl;
	}
	system("pause");
	system("cls");
}
void WorkerManager::clearEmp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "记录不存在或为空" << endl;
	}
	else
	{
		cout << "确定清空？" << endl;
		cout << "1.确定" << endl;
		cout << "2.取消" << endl;
		char select;
		cin >> select;
		while (select < '1' || select>'2')
		{
			cout << "输入有误！" << endl;
			cout << "确定清空？" << endl;
			cout << "1.确定" << endl;
			cout << "2.取消" << endl;
			cin >> select;
		}
		if (select == '1')
		{
			ofstream ofs;
			ofs.open(FILENAME, ios::trunc); //删除文件重新新建
			ofs.close();
			if (this->m_EmpArray != NULL)
			{
				//删除堆区的每个职工对象
				for (int i = 0; i < this->m_EmpNum; i++)
				{
					if (this->m_EmpArray[i] != NULL)
					{
						delete this->m_EmpArray[i];
						this->m_EmpArray[i] = NULL;
					}
				}
				//删除堆区数组指针
				delete[] this->m_EmpArray;
				this->m_EmpArray = NULL;
				this->m_EmpNum = 0;
				this->m_FileIsEmpty = true;
			}
			cout << "清除成功" << endl;

		}
		else
		{
			cout << "取消成功" << endl;
		}
	}
	system("pause");
	system("cls");
}
void WorkerManager::showForm()
{
	if (this->m_FileIsEmpty)
	{
		cout << "记录不存在或为空" << endl;
	}
	else
	{
		if (this->m_EmpArray != NULL)
		{
			ofstream ofs;
			ofs.open(CSVFILENAME, ios::out);
			ofs << "职工编号" << ","
				<< "职工姓名" << ","
				<< "职工岗位" << endl;
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				ofs << this->m_EmpArray[i]->m_Id << ","
					<< this->m_EmpArray[i]->m_Name << ","
					<< this->m_EmpArray[i]->getDeptName() << endl;
			}
			ofs.close();
			cout << "已保存至" << CSVFILENAME << endl;
		}
	}
	system("pause");
	system("cls");
}