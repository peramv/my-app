#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_receiving_acct_and_relinquishing_acct_linked_to_diff_ams_model : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_receiving_acct_and_relinquishing_acct_linked_to_diff_ams_model() { }
		~CIFast_IFast_ifastcbo_err_receiving_acct_and_relinquishing_acct_linked_to_diff_ams_model() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_RECEIVING_ACCT_AND_RELINQUISHING_ACCT_LINKED_TO_DIFF_AMS_MODEL")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The receiving account and relinquishing account are linked to different AMS models.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("The receiving account and relinquishing account are linked to different AMS models.")); }

        // Actions
	};
}