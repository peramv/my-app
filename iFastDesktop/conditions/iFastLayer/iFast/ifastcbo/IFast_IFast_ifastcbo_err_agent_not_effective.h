#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_agent_not_effective : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_agent_not_effective() { }
		~CIFast_IFast_ifastcbo_err_agent_not_effective() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_AGENT_NOT_EFFECTIVE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Agent is not effective until %DATE%.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Agent is not effective until %DATE%.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Agent is not effective until %DATE%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'agent n'est pas en vigueur avant le %DATE%.")); }

        // Actions
	};
}



