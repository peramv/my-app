#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_fund_marked_no_ach_activy : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_fund_marked_no_ach_activy() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_fund_marked_no_ach_activy() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_FUND_MARKED_NO_ACH_ACTIVY")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The account number does not exist.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("The account number does not exist.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Die Kontonummer existiert nicht.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El número de cuenta no existe.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Numéro de compte inexistant")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Het accountnummer bestaat niet")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("please re-enter")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("please re-enter")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Bitte geben Sie neu ein.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("please re-enter")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Veuillez recommencer la saisie.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("vul opnieuw in")); }
	};
}



