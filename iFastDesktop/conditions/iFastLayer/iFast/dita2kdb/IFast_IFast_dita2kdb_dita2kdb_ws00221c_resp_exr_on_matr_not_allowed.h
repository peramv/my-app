#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_exr_on_matr_not_allowed : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_exr_on_matr_not_allowed() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_exr_on_matr_not_allowed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_EXR_ON_MATR_NOT_ALLOWED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("%ACCOUNT_TYPE% already exists for year %EFFECTIVE_DATE%.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("%ACCOUNT_TYPE% already exists for year %EFFECTIVE_DATE%.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("%ACCOUNT_TYPE% existiert bereits für das Jahr %EFFECTIVE_DATE%.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("%ACCOUNT_TYPE% ya existe para el año %EFFECTIVE_DATE%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le %ACCOUNT_TYPE% existe déjà pour l'année %EFFECTIVE_DATE%.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("%ACCOUNT_TYPE% bestaat al voor jaar %EFFECTIVE_DATE%")); }

        // Actions
	};
}



