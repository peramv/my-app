#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_compensation_agent_must_be_changed : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_compensation_agent_must_be_changed() { }
		~CIFast_IFast_ifastcbo_err_compensation_agent_must_be_changed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_COMPENSATION_AGENT_MUST_BE_CHANGED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The Compensation Agent must be changed before changing the Service Agent.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'agent de commission doit être changé avant l'agent de service.")); }

        // Actions
	};
}



