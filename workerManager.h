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

	void ShowMenu(); //展示菜单
	void ExitSystem(); //退出系统
	void AddEmp(); //添加职工
	void save(); //保存文件
	int getEmpNum(); //统计文件中人数
	void initEmp(); //初始化职工
	void showEmp(); //显示职工
	void delEmp(); //删除职工
	int isExist(int id); //判断职工是否存在
	void modEmp() ;//修改职工信息
	void findEmp(); //查找职工信息
	void sortEmp(); //按照编号排序
	void clearEmp(); //清空所有信息
	void showForm(); //输出到csv表


	~WorkerManager();

	int m_EmpNum; //记录职工人数
	Worker** m_EmpArray; //职工数组指针
	bool m_FileIsEmpty; //文件是否为空 标志
};