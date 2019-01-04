#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_fund_relationship : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_fund_relationship() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_fund_relationship() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_INVALID_FUND_RELATIONSHIP")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Index Rate must be between 0 and 20.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Index Rate must be between 0  and 20.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Indexsatz muss zwischen 0 und 20 liegen.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La tasa de índice debe ser entre 0 y 20.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le taux d'indexation doit être situé entre 0 et 20.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Indexpercentage moet tussen 0 en 20 liggen")); }

        // Actions
	};
}



