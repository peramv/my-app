#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_trade_date_equal_or_greater_than_purchase_date : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_trade_date_equal_or_greater_than_purchase_date() { }
		~CIFast_IFast_ifastcbo_err_trade_date_equal_or_greater_than_purchase_date() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_TRADE_DATE_MUST_BE_EQUAL_OR_GREATER_THAN_PURCHASE_DATE ")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Trade date must be greater than or equal to original purchase date.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La date de transaction doit être postérieure ou identique à celle du premier achat.")); }

        // Actions
	};
}
