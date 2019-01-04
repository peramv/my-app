#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_acct_closed : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_acct_closed() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_acct_closed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_ACCT_CLOSED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("No Date of Birth was entered.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("No Date of Birth was entered.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Es wurde kein Geburtsdatum eingegeben.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se introdujo una fecha de nacimiento")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Aucune date de naissance n'a été saisie.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er is geen geboortedatum opgegeven")); }

        // Actions
	};
}



