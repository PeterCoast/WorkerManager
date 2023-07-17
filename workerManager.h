#pragma once
#include<iostream>
using namespace std;
#include "worker.h"
#include"employee.h"
#include "manager.h"
#include"boss.h"
#define FILENAME "./data/empFile.txt"
#define CSVFILENAME "./data/empFile.csv"
#include <fstream>
#include<cstdlib>


class WorkerManager
{
public:
	WorkerManager();

	void ShowMenu(); //չʾ�˵�
	void ExitSystem(); //�˳�ϵͳ
	void AddEmp(); //���ְ��
	void save(); //�����ļ�
	int getEmpNum(); //ͳ���ļ�������
	void initEmp(); //��ʼ��ְ��
	void showEmp(); //��ʾְ��
	void delEmp(); //ɾ��ְ��
	int isExist(int id); //�ж�ְ���Ƿ����
	void modEmp() ;//�޸�ְ����Ϣ
	void findEmp(); //����ְ����Ϣ
	void sortEmp(); //���ձ������
	void clearEmp(); //���������Ϣ
	void showForm(); //�����csv��


	~WorkerManager();

	int m_EmpNum; //��¼ְ������
	Worker** m_EmpArray; //ְ������ָ��
	bool m_FileIsEmpty; //�ļ��Ƿ�Ϊ�� ��־
};