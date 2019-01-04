#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_employee_agent_bonus_purchase_only_applicable_for_employ_agent : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_employee_agent_bonus_purchase_only_applicable_for_employ_agent() { }
		~CIFast_IFast_ifastcbo_err_employee_agent_bonus_purchase_only_applicable_for_employ_agent() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_EMPLOYEE_AGENT_BONUS_PURCHASE_ONLY_APPLICABLE_FOR_EMPLOY_AGENT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Employee/Agent Bonus Purchase is only applicable for Employee/Agent accounts.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le dépôt du boni employé/agent ne s'applique qu'aux comptes employé/agent.")); }

        // Actions
	};
}



