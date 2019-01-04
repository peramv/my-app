#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_alloc_amt_exceeds_trade_amt : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_alloc_amt_exceeds_trade_amt() { }
		~CIFast_IFast_ifastcbo_err_alloc_amt_exceeds_trade_amt() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ALLOC_AMT_EXCEEDS_TRADE_AMT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Sum of allocation amounts exceeds investment amount.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La somme des montants de répartition excède le montant d'investissement.")); }

        // Actions
	};
}



