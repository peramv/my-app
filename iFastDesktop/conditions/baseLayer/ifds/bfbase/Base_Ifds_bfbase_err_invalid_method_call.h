#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Ifds_bfbase_err_invalid_method_call : public CConditionObject
	{
	public:
		CBase_Ifds_bfbase_err_invalid_method_call() { }
		~CBase_Ifds_bfbase_err_invalid_method_call() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_METHOD_CALL")); }
		virtual DString GetGroupName() const { return DString(I_("ifds")); }
		virtual DString GetModuleName() const { return DString(I_("bfbase")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Encorr Already Loaded.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Encorr Already Loaded.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Für dieses Konto wurde %TRADE_TYPE% gestoppt. %TRADE_TYPE% kann nicht erstellt werden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Encorr Already Loaded.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("EnCorr déjà chargé.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Encorr is al geladen.")); }

        // Actions
		virtual DString GetAction_ES_ES() const { return DString(I_("NULL")); }
	};
}



