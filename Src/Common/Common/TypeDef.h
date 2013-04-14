#pragma once
#include <vector>

using namespace std;

//版本
#define APP_NAME     _T("福瑞堂医药管理系统")

//基础数据结构
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
