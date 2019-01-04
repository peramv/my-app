#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_agent_tpa_same : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_agent_tpa_same() { }
		~CIFast_IFast_ifastcbo_err_agent_tpa_same() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_AGENT_TPA_SAME")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Agent For Firm and TPA should not be the same.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Agent For Firm and TPA should not be the same.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'agent de cabinet et TPA ne devraient pas être identiques.")); }

        // Actions
	};
}



