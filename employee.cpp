#include"employee.h"
Employee::Employee(int id, string name, int dId)
{
	this->m_Id = id;
	this->m_Name = name;
	this->m_DeptId = dId;
}

void Employee::showInfo()
{
	cout << "Ա����ţ�" << this->m_Id
		<< "\tԱ��������" << this->m_Name
		<< "\tԱ����λ��" << this->getDeptName() << endl;
}

string Employee::getDeptName()
{
	return string("Ա��");
}