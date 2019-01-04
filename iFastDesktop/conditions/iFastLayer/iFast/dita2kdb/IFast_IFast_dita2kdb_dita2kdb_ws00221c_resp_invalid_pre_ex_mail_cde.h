#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_pre_ex_mail_cde : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_pre_ex_mail_cde() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_pre_ex_mail_cde() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_INVALID_PRE_EX_MAIL_CDE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Account tax type does not match the group tax type.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Account tax type does not match the group tax type.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Konto-Steuerart stimmt nicht mit der Gruppen-Steuerart überein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El tipo tributario de la cuenta no coincide con el tipo tributario del grupo.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le type d'imposition du compte ne correspond pas au type d'imposition du groupe.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Belastingtype account komt niet overeen met belastingtype groep")); }

        // Actions
	};
}



