#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_agentforfirm_not_related_to_clearingfirm : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_agentforfirm_not_related_to_clearingfirm() { }
		~CIFast_IFast_ifastcbo_err_agentforfirm_not_related_to_clearingfirm() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_AGENTFORFIRM_NOT_RELATED_TO_CLEARINGFIRM")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Agent for Firm is not related to the Clearing Firm.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Agent for Firm is not related to the Clearing Firm.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'agent de cabinet n'est pas affilié au cabinet de compensation.")); }

        // Actions
	};
}



