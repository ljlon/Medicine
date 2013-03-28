#pragma once
#include <vector>

using namespace std;

//�汾
#define APP_NAME     _T("������ҽҩ����ϵͳ")

//�������ݽṹ
typedef struct _TreeStruct 
{
	CString csNodeName;
	vector<_TreeStruct*> vctChildTree;

	_TreeStruct()
	{
		
	}

	~_TreeStruct()
	{
		for (unsigned int i = 0; i < vctChildTree.size(); i++)
		{
			if (vctChildTree.at(i) != NULL)
			{
				delete vctChildTree.at(i);
				vctChildTree.at(i) = NULL;
			}
		}
	}
}TreeStruct;
