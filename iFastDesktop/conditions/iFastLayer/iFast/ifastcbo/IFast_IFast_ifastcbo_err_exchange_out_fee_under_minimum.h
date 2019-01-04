#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_exchange_out_fee_under_minimum : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_exchange_out_fee_under_minimum() { }
		~CIFast_IFast_ifastcbo_err_exchange_out_fee_under_minimum() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_EXCHANGE_OUT_FEE_UNDER_MINIMUM")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Exchange out fee is under the minimum.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Exchange out fee is under the minimum.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Exchange out fee is under the minimum.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les frais d'échange sortant sont inférieurs au minimum.")); }

        // Actions
	};
}



