#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_different_accountable_than_cancellation_not_through_fundserv : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_different_accountable_than_cancellation_not_through_fundserv() { }
		~CIFast_IFast_ifastcbo_warn_different_accountable_than_cancellation_not_through_fundserv() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_DIFFERENT_ACCOUNTABLE_THAN_CANCELLATION_NOT_THROUGH_FUNDSERV")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Both dilution amounts of Cancellation and Rebook will not be settled through FundSERV if Accountables are different.")); }

        // Actions
	};
}



