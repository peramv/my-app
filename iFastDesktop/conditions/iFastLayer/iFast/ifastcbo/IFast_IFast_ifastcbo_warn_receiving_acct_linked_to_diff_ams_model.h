#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_receiving_acct_linked_to_diff_ams_model : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_receiving_acct_linked_to_diff_ams_model() { }
		~CIFast_IFast_ifastcbo_warn_receiving_acct_linked_to_diff_ams_model() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_RECEIVING_ACCT_LINKED_TO_DIFF_AMS_MODEL")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The receiving account is linked to a different global AMS model.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("The receiving account is linked to a different global AMS model.")); }

        // Actions
	};
}