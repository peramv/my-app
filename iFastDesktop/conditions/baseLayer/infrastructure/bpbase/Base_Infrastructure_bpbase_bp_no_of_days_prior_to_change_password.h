#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Infrastructure_bpbase_bp_no_of_days_prior_to_change_password : public CConditionObject
	{
	public:
		CBase_Infrastructure_bpbase_bp_no_of_days_prior_to_change_password() { }
		~CBase_Infrastructure_bpbase_bp_no_of_days_prior_to_change_password() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("BP_NO_OF_DAYS_PRIOR_TO_CHANGE_PASSWORD")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("bpbase")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Changed by different operator.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Changed by different operator.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Geändert durch einen anderen Operator.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Cambiado por otro operador.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Changé par un opérateur différent")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Gewijzigd door een andere operator")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Check system.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Verifiez le systeme.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Überprüfen Sie das System.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Verifique el sistema.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Vérifiez le système.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Controleer het systeem")); }
	};
}



