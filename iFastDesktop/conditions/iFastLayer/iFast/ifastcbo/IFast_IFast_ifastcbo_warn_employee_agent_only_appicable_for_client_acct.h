#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_employee_agent_only_appicable_for_client_acct : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_employee_agent_only_appicable_for_client_acct() { }
		~CIFast_IFast_ifastcbo_warn_employee_agent_only_appicable_for_client_acct() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_EMPLOYEE_AGENT_ONLY_APPICABLE_FOR_CLIENT_ACCT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Only client account is applicable to set up Employee/Agent funds relationship.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Seul le compte client est applicable pour la relation avec les fonds employé/agent.")); }

        // Actions
	};
}



