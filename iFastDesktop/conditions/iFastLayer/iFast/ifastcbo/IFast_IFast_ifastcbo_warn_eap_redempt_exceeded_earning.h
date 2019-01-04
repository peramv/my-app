#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_eap_redempt_exceeded_earning : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_eap_redempt_exceeded_earning() { }
		~CIFast_IFast_ifastcbo_warn_eap_redempt_exceeded_earning() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_EAP_REDEMPT_EXCEEDED_EARNING")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Redemption Charges %PARAM_1% exceed Earnings %PARAM_2%. Waive the charges or system will deduct them  from the account holdings/contribution.")); }

        // Actions
	};
}



