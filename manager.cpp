#include"manager.h"

Manager::Manager(int id, string name, int dId)
{
	this->m_Id = id;
	this->m_Name = name;
	this->m_DeptId = dId;
}
void Manager::showInfo()
{
	cout << "Ա����ţ�" << this->m_Id
		<< "\tԱ��������" << this->m_Name
		<< "\tԱ����λ��" << this->getDeptName() << endl;
}

string Manager::getDeptName()
{
	return string("����");
}