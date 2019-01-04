#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_plan_code_not_found : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_plan_code_not_found() { }
		~CIFast_IFast_ifastdbrkr_err_plan_code_not_found() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_PLAN_CODE_NOT_FOUND")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Plan Code not found.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Plancode nicht gefunden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se encontró el código del plan.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Code de régime introuvable")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Plancode is niet gevonden")); }

        // Actions
	};
}



