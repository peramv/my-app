#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_last_acct_number_assigned : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_last_acct_number_assigned() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_last_acct_number_assigned() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_LAST_ACCT_NUMBER_ASSIGNED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Amount must be greater than zero.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Amount must be greater than zero.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Betrag muss größer als Null sein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El monto debe ser superior a cero.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le montant doit être supérieur à zéro.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Bedrag moet groter dan nul zijn")); }

        // Actions
	};
}



