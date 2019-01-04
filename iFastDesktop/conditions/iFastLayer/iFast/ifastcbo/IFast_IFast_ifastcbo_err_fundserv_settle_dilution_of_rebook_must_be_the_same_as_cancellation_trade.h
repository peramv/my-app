#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_fundserv_settle_dilution_of_rebook_must_be_the_same_as_cancellation_trade : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_fundserv_settle_dilution_of_rebook_must_be_the_same_as_cancellation_trade() { }
		~CIFast_IFast_ifastcbo_err_fundserv_settle_dilution_of_rebook_must_be_the_same_as_cancellation_trade() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FUNDSERV_SETTLE_DILUTION_OF_REBOOK_MUST_BE_THE_SAME_AS_CANCELLATION_TRADE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The Dilution amount should be settled OR not settled through FundSERV the same for Cancellation and Rebook.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("The Dilution amount should be settled OR not settled through FundSERV the same for Cancellation and Rebook.")); }


        // Actions
	};
}



