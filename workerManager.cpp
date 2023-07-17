#include "workerManager.h"
WorkerManager::WorkerManager()
{
	system("mkdir data");
	system("cls");
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	if (!ifs.is_open())
	{
		//�ļ���ʧ��
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
		//�ļ����� ��Ϊ��
		this->m_EmpNum = 0;
		this->m_EmpArray = NULL;
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}

	//�ļ����� �����м�¼����
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
	cout << "******  ��ӭʹ��ְ������ϵͳ *******" << endl;
	cout << "*********  1.����ְ����Ϣ  *********" << endl;
	cout << "*********  2.��ʾְ����Ϣ  *********" << endl;
	cout << "*********  3.ɾ����ְְ��  *********" << endl;
	cout << "*********  4.�޸�ְ����Ϣ  *********" << endl;
	cout << "*********  5.����ְ����Ϣ  *********" << endl;
	cout << "*********  6.���ձ������  *********" << endl;
	cout << "*********  7.���������Ϣ  *********" << endl;
	cout << "*********  8.����������  *********" << endl;
	cout << "*********  0.�˳�����ϵͳ  *********" << endl;
	cout << "************************************" << endl;
	cout << endl << "����������ѡ��";
}

void WorkerManager::ExitSystem()
{
	cout << "��ӭ�´�ʹ��" << endl;
	system("pause");
	exit(0);
}

void WorkerManager::AddEmp()
{
	cout << "���������ְ������" << endl;
	int addNum = 0;
	cin >> addNum;
	if (addNum > 0)
	{
		int newSize = this->m_EmpNum + addNum; //�¿ռ�����

		Worker** newSpace = new Worker * [newSize];

		//�Ѿ����ݿ������¿ռ���
		if (this->m_EmpArray != NULL)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				newSpace[i] = this->m_EmpArray[i];
			}
		}

		//�������������
		for (int i = 0; i < addNum; i++)
		{
			int id; //ְ�����
			string name; //ְ������
			char dSelect; //����ѡ��

			cout << "�������" << i + 1 << "����ְ�����" << endl;
			cin >> id;

			cout << "�������" << i + 1 << "����ְ������" << endl;
			cin >> name;

			cout << "��ѡ���ְ����λ��" << endl;
			cout << "1.��ְͨ��" << endl;
			cout << "2.����" << endl;
			cout << "3.�ϰ�" << endl;
			cin >> dSelect;
			while (dSelect < '1' || dSelect > '3')
			{
				cout << "��������" << endl;
				cout << "��ѡ���ְ����λ��" << endl;
				cout << "1.��ְͨ��" << endl;
				cout << "2.����" << endl;
				cout << "3.�ϰ�" << endl;
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

		cout << "�ɹ����" << addNum << "����ְ��" << endl;
		this->save();
	}
	else
	{
		cout << "������������" << endl;
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
		if (int(dId - 48) == 1) //��ͨԱ��
		{
			worker = new Employee(int(id - 48), name, int(dId - 48));
		}
		else if (int(dId - 48) == 2) //����
		{
			worker = new Manager(int(id - 48), name, int(dId - 48));
		}
		else //�ϰ�
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
		cout << "��¼�����ڻ�Ϊ��" << endl;
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
		cout << "��¼�����ڻ�Ϊ��" << endl;
	}
	else
	{
		cout << "������Ҫɾ����ְ�����" << endl;
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
			cout << "ɾ���ɹ�" << endl;
		}
		else
		{
			cout << "���޴���" << endl;
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
		cout << "��¼�����ڻ�Ϊ��" << endl;
	}
	else
	{
		cout << "������Ҫ�޸ĵ�ְ�����" << endl;
		int id = 0;
		cin >> id;
		int ret = this->isExist(id);
		if (ret != -1)
		{
			int id; //ְ�����
			string name; //ְ������
			char dSelect; //����ѡ��

			cout << "������ְ�����" << endl;
			cin >> id;

			cout << "������ְ������" << endl;
			cin >> name;

			cout << "��ѡ���ְ����λ��" << endl;
			cout << "1.��ְͨ��" << endl;
			cout << "2.����" << endl;
			cout << "3.�ϰ�" << endl;
			cin >> dSelect;
			while (dSelect < '1' || dSelect > '3')
			{
				cout << "��������" << endl;
				cout << "��ѡ���ְ����λ��" << endl;
				cout << "1.��ְͨ��" << endl;
				cout << "2.����" << endl;
				cout << "3.�ϰ�" << endl;
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
			cout << "�޸ĳɹ�" << endl;
		}
		else
		{
			cout << "���޴���" << endl;
		}
	}
	system("pause");
	system("cls");
}
void WorkerManager::findEmp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "��¼�����ڻ�Ϊ��" << endl;
	}
	else
	{
		cout << "��ѡ����ҷ�ʽ��" << endl;
		cout << "1.����ְ�����" << endl;
		cout << "2.����ְ������" << endl;
		char select;
		cin >> select;
		while (select < '1' || select>'2')
		{
			cout << "��������" << endl;
			cout << "��ѡ����ҷ�ʽ��" << endl;
			cout << "1.����ְ�����" << endl;
			cout << "2.����ְ������" << endl;
			cin >> select;
		}
		if (select == '1') {
			cout << "������Ҫ���ҵ�ְ�����" << endl;
			int id = 0;
			cin >> id;
			int ret = this->isExist(id);
			if (ret != -1)
			{
				cout << "���ҳɹ���" << endl;
				this->m_EmpArray[ret]->showInfo();
			}
			else
			{
				cout << "���޴���" << endl;
			}
		}
		else
		{
			cout << "������Ҫ���ҵ�ְ������" << endl;
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
				cout << "���޴���" << endl;
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
		cout << "��¼�����ڻ�Ϊ��" << endl;
	}
	else
	{
		cout << "��ѡ������ʽ" << endl;
		cout << "1.����ְ���������" << endl;
		cout << "2.����ְ����Ž���" << endl;
		char select;
		cin >> select;
		while (select < '1' || select>'2')
		{
			cout << "��������" << endl;
			cout << "��ѡ������ʽ" << endl;
			cout << "1.����ְ���������" << endl;
			cout << "2.����ְ����Ž���" << endl;
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
		cout << "�������" << endl;
	}
	system("pause");
	system("cls");
}
void WorkerManager::clearEmp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "��¼�����ڻ�Ϊ��" << endl;
	}
	else
	{
		cout << "ȷ����գ�" << endl;
		cout << "1.ȷ��" << endl;
		cout << "2.ȡ��" << endl;
		char select;
		cin >> select;
		while (select < '1' || select>'2')
		{
			cout << "��������" << endl;
			cout << "ȷ����գ�" << endl;
			cout << "1.ȷ��" << endl;
			cout << "2.ȡ��" << endl;
			cin >> select;
		}
		if (select == '1')
		{
			ofstream ofs;
			ofs.open(FILENAME, ios::trunc); //ɾ���ļ������½�
			ofs.close();
			if (this->m_EmpArray != NULL)
			{
				//ɾ��������ÿ��ְ������
				for (int i = 0; i < this->m_EmpNum; i++)
				{
					if (this->m_EmpArray[i] != NULL)
					{
						delete this->m_EmpArray[i];
						this->m_EmpArray[i] = NULL;
					}
				}
				//ɾ����������ָ��
				delete[] this->m_EmpArray;
				this->m_EmpArray = NULL;
				this->m_EmpNum = 0;
				this->m_FileIsEmpty = true;
			}
			cout << "����ɹ�" << endl;

		}
		else
		{
			cout << "ȡ���ɹ�" << endl;
		}
	}
	system("pause");
	system("cls");
}
void WorkerManager::showForm()
{
	if (this->m_FileIsEmpty)
	{
		cout << "��¼�����ڻ�Ϊ��" << endl;
	}
	else
	{
		if (this->m_EmpArray != NULL)
		{
			ofstream ofs;
			ofs.open(CSVFILENAME, ios::out);
			ofs << "ְ�����" << ","
				<< "ְ������" << ","
				<< "ְ����λ" << endl;
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				ofs << this->m_EmpArray[i]->m_Id << ","
					<< this->m_EmpArray[i]->m_Name << ","
					<< this->m_EmpArray[i]->getDeptName() << endl;
			}
			ofs.close();
			cout << "�ѱ�����" << CSVFILENAME << endl;
		}
	}
	system("pause");
	system("cls");
}