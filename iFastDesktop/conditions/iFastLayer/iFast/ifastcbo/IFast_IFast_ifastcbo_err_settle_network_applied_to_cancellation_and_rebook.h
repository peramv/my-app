#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_settle_network_applied_to_cancellation_and_rebook : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_settle_network_applied_to_cancellation_and_rebook() { }
		~CIFast_IFast_ifastcbo_err_settle_network_applied_to_cancellation_and_rebook() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_SETTLE_NETWORK_APPLIED_TO_CANCELLATION_AND_REBOOK")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The same SettleNetwork will be applied to both Cancellation and Rebook; neither will be settled through FundSERV.")); }

        // Actions
	};
}



