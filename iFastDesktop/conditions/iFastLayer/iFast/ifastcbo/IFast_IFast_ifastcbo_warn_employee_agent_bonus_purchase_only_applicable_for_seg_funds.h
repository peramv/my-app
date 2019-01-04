#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_employee_agent_bonus_purchase_only_applicable_for_seg_funds : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_employee_agent_bonus_purchase_only_applicable_for_seg_funds() { }
		~CIFast_IFast_ifastcbo_warn_employee_agent_bonus_purchase_only_applicable_for_seg_funds() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_EMPLOYEE_AGENT_BONUS_PURCHASE_ONLY_APPLICABLE_FOR_SEG_FUNDS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Employee/Agent Bonus Purchase is not applicable for %FUND_CATEGORY%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le dépôt du boni employé/agent ne s'applique pas aux fonds %FUND_CATEGORY%.")); }

        // Actions
	};
}



