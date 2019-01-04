#pragma once

#include "stdafx.h"

class CConditionObject;

class CConditionBuilder
{
public:
	static CConditionBuilder* Instance();

    CConditionObject* GetCondition(long code, DString& strModuleName, DString& strLocale, DString& strClient, DString& strMarket, const DString& strDataFolderPath);

    void CheckForOverrides(CConditionObject* pConditionObject, const DString& strDataFolderPath);

private:
	CConditionObject* CreateBaseIfdsConditionObject(long conditionId);
	CConditionObject* CreateBaseInfrastructureConditionObject(long conditionId);

	CConditionObject* CreateIFastIFastConditionObject(long conditionId);
	CConditionObject* CreateIFastInfrastructureConditionObject(long conditionId);

	CConditionBuilder(){};  
	CConditionBuilder(CConditionBuilder const&){};             
	CConditionBuilder& operator=(CConditionBuilder const&){};
	
	static CConditionBuilder* m_pInstance;
};
