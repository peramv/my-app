#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_resp_plan_limit_exceeded : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_resp_plan_limit_exceeded() { }
		~CIFast_IFast_ifastcbo_warn_resp_plan_limit_exceeded() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_RESP_PLAN_LIMIT_EXCEEDED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("RESP Beneficiary’s %BENNAME% Lifetime Contribution has exceeded %LIFETIMELIMIT%.  Lifetime Contribution todate is %TODATE%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La cotisation viagère du bénéficiaire REEE %BENNAME% a excédé le plafond de %LIFETIMELIMIT%. La cotisation viagère à ce jour est de %TODATE%.")); }

        // Actions
	};
}



