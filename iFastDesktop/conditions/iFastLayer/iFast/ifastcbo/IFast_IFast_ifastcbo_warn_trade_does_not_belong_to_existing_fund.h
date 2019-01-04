#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_trade_does_not_belong_to_existing_fund : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_trade_does_not_belong_to_existing_fund() { }
		~CIFast_IFast_ifastcbo_warn_trade_does_not_belong_to_existing_fund() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_TRADE_DOES_NOT_BELONG_TO_EXISTING_FUND")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Account/Contract Type cannot hold more than one fund.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Un seul fonds est permis sur ce type de contrat.")); }

        // Actions
	};
}



