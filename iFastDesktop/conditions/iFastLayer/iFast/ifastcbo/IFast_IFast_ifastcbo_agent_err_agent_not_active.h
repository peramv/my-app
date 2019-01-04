#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_agent_err_agent_not_active : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_agent_err_agent_not_active() { }
		~CIFast_IFast_ifastcbo_agent_err_agent_not_active() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("AGENT_ERR_AGENT_NOT_ACTIVE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Agent is not active.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Agent is not active.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Agent is not active.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Agent inactif")); }

        // Actions
	};
}



