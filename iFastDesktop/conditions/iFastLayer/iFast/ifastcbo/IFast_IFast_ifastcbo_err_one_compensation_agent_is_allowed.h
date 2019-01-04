#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_one_compensation_agent_is_allowed : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_one_compensation_agent_is_allowed() { }
		~CIFast_IFast_ifastcbo_err_one_compensation_agent_is_allowed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ONE_COMPENSATION_AGENT_IS_ALLOWED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Only one Compensation Agent is applicable for a FundSERV broker, delete other compensation agents for this account.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Un seul agent de commission est applicable pour un courtier FundSERV; supprimez les autres agents de commission pour ce compte.")); }

        // Actions
	};
}



