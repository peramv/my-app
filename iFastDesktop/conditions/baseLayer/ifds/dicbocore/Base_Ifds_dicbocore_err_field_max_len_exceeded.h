#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Ifds_dicbocore_err_field_max_len_exceeded : public CConditionObject
	{
	public:
		CBase_Ifds_dicbocore_err_field_max_len_exceeded() { }
		~CBase_Ifds_dicbocore_err_field_max_len_exceeded() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FIELD_MAX_LEN_EXCEEDED")); }
		virtual DString GetGroupName() const { return DString(I_("ifds")); }
		virtual DString GetModuleName() const { return DString(I_("dicbocore")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("OLE Automation Error:%OLEMSG%")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("OLE Automation Error:%OLEMSG%")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Für dieses Konto wurden Transfers/Börsenhandel gestoppt. Automatischer Transfer kann nicht erstellt werden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("OLE Automation Error:%OLEMSG%")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Erreur d'automatisation OLE : %OLEMSG%")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("OLE-automatiseringsfout:%OLEMSG%")); }

        // Actions
		virtual DString GetAction_ES_ES() const { return DString(I_("NULL")); }
	};
}



