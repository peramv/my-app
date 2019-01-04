#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_resp_plan_limit_exceeded : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_resp_plan_limit_exceeded() { }
		~CIFast_IFast_ifastdbrkr_err_resp_plan_limit_exceeded() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_RESP_PLAN_LIMIT_EXCEEDED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("RESP Plan Limit exceeded.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("RESP-Plangrenze überschritten.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Se ha excedido el límite del plan RESP.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La cotisation viagère du bénéficiaire REEE %BENNAME% a excédé le plafond de %LIFETIMELIMIT%. La cotisation viagère à ce jour est de %TODATE%.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Limiet RESP-plan is overschreden")); }

        // Actions
	};
}



