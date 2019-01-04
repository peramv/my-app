#pragma once

#include "stdafx.h"

class CConditionObject
{
public:
	CConditionObject() 
    { 
        m_strClientName = I_(""); 
        m_strMarketName = I_("");

        m_nSeverityOverride = -1;

        m_strMessageOverride_EN_US = I_("");
        m_strMessageOverride_FR_FR = I_("");
        m_strMessageOverride_DE_DE = I_("");
        m_strMessageOverride_ES_ES = I_("");
        m_strMessageOverride_FR_CA = I_("");
        m_strMessageOverride_NL_NL = I_("");
        
        m_strActionOverride_EN_US = I_("");
        m_strActionOverride_FR_FR = I_("");
        m_strActionOverride_DE_DE = I_("");
        m_strActionOverride_ES_ES = I_("");
        m_strActionOverride_FR_CA = I_("");
        m_strActionOverride_NL_NL = I_("");
    }

	~CConditionObject() { }

public:
	// General
	void SetClientName(DString& strClientName) { m_strClientName = strClientName; }
	DString GetClientName() const { return m_strClientName; }

	void SetMarketName(DString& strMarketName) { m_strMarketName = strMarketName; }
	virtual DString GetMarketName() const { return m_strMarketName; }

    virtual DString GetConditionName() const { return DString(I_("")); }
	virtual DString GetGroupName() const { return DString(I_("")); }
	virtual DString GetModuleName() const { return DString(I_("")); }
	virtual int GetSeverity() const { return -1; }

	void SetSeverityOverride(int nSeverityOverride) { m_nSeverityOverride = nSeverityOverride; }
	virtual int GetSeverityOverride() const { return m_nSeverityOverride; }

	virtual int GetSuppress() const { return 0; }
	
	// Get messages
	virtual DString GetMessage_EN_US() const { return DString(I_("")); }
	virtual DString GetMessage_FR_FR() const { return GetMessage_EN_US(); }
	virtual DString GetMessage_DE_DE() const { return GetMessage_EN_US(); }
	virtual DString GetMessage_ES_ES() const { return GetMessage_EN_US(); }
	virtual DString GetMessage_FR_CA() const { return GetMessage_EN_US(); }
	virtual DString GetMessage_NL_NL() const { return GetMessage_EN_US(); }

	// Set message overrides
	void SetMessageOverride_EN_US(DString& strMessageOverride_EN_US) { m_strMessageOverride_EN_US = strMessageOverride_EN_US; }
	void SetMessageOverride_FR_FR(DString& strMessageOverride_FR_FR) { m_strMessageOverride_FR_FR = strMessageOverride_FR_FR; }
	void SetMessageOverride_DE_DE(DString& strMessageOverride_DE_DE) { m_strMessageOverride_DE_DE = strMessageOverride_DE_DE; }
	void SetMessageOverride_ES_ES(DString& strMessageOverride_ES_ES) { m_strMessageOverride_ES_ES = strMessageOverride_ES_ES; }
	void SetMessageOverride_FR_CA(DString& strMessageOverride_FR_CA) { m_strMessageOverride_FR_CA = strMessageOverride_FR_CA; }
	void SetMessageOverride_NL_NL(DString& strMessageOverride_NL_NL) { m_strMessageOverride_NL_NL = strMessageOverride_NL_NL; }
		
	// Get message overrides
	virtual DString GetMessageOverride_EN_US() const { return m_strMessageOverride_EN_US; }
	virtual DString GetMessageOverride_FR_FR() const { return m_strMessageOverride_FR_FR; }
	virtual DString GetMessageOverride_DE_DE() const { return m_strMessageOverride_DE_DE; }
	virtual DString GetMessageOverride_ES_ES() const { return m_strMessageOverride_ES_ES; }
	virtual DString GetMessageOverride_FR_CA() const { return m_strMessageOverride_FR_CA; }
	virtual DString GetMessageOverride_NL_NL() const { return m_strMessageOverride_NL_NL; }
		
    // Get actions
	virtual DString GetAction_EN_US() const { return DString(I_("")); }
	virtual DString GetAction_FR_FR() const { return GetAction_EN_US(); }
	virtual DString GetAction_DE_DE() const { return GetAction_EN_US(); }
	virtual DString GetAction_ES_ES() const { return GetAction_EN_US(); }
	virtual DString GetAction_FR_CA() const { return GetAction_EN_US(); }
	virtual DString GetAction_NL_NL() const { return GetAction_EN_US(); }

    // Set action overrides
	void SetActionOverride_EN_US(DString& strActionOverride_EN_US) { m_strActionOverride_EN_US = strActionOverride_EN_US; }
	void SetActionOverride_FR_FR(DString& strActionOverride_FR_FR) { m_strActionOverride_FR_FR = strActionOverride_FR_FR; }
	void SetActionOverride_DE_DE(DString& strActionOverride_DE_DE) { m_strActionOverride_DE_DE = strActionOverride_DE_DE; }
	void SetActionOverride_ES_ES(DString& strActionOverride_ES_ES) { m_strActionOverride_ES_ES = strActionOverride_ES_ES; }
	void SetActionOverride_FR_CA(DString& strActionOverride_FR_CA) { m_strActionOverride_FR_CA = strActionOverride_FR_CA; }
	void SetActionOverride_NL_NL(DString& strActionOverride_NL_NL) { m_strActionOverride_NL_NL = strActionOverride_NL_NL; }

    // Get action overrides
	virtual DString GetActionOverride_EN_US() const { return m_strActionOverride_EN_US; }
	virtual DString GetActionOverride_FR_FR() const { return m_strActionOverride_FR_FR; }
	virtual DString GetActionOverride_DE_DE() const { return m_strActionOverride_DE_DE; }
	virtual DString GetActionOverride_ES_ES() const { return m_strActionOverride_ES_ES; }
	virtual DString GetActionOverride_FR_CA() const { return m_strActionOverride_FR_CA; }
	virtual DString GetActionOverride_NL_NL() const { return m_strActionOverride_NL_NL; }

protected:
    DString m_strClientName;
    DString m_strMarketName;

    int m_nSeverityOverride;

	DString m_strMessageOverride_EN_US;
	DString m_strMessageOverride_FR_FR;
	DString m_strMessageOverride_DE_DE;
	DString m_strMessageOverride_ES_ES;
	DString m_strMessageOverride_FR_CA;
	DString m_strMessageOverride_NL_NL;

	DString m_strActionOverride_EN_US;
	DString m_strActionOverride_FR_FR;
	DString m_strActionOverride_DE_DE;
	DString m_strActionOverride_ES_ES;
	DString m_strActionOverride_FR_CA;
	DString m_strActionOverride_NL_NL;
};                                                                     
