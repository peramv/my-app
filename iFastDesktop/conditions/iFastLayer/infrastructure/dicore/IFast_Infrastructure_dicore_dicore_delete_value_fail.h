#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_dicore_dicore_delete_value_fail : public CConditionObject
	{
	public:
		CIFast_Infrastructure_dicore_dicore_delete_value_fail() { }
		~CIFast_Infrastructure_dicore_dicore_delete_value_fail() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DICORE_DELETE_VALUE_FAIL")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("dicore")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("There is an internal problem.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("There is an internal problem.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Es gibt ein internes Problem.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Hay un problema interno.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Il y a un problème interne.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er is een intern probleem")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Contact a support representative.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Contactez un representant en assistance technique.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Wenden Sie sich an einen Support-Mitarbeiter.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Contact a support representative.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Communiquez avec un représentant technique.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Neem contact op met een supportmedewerker")); }
	};
}



