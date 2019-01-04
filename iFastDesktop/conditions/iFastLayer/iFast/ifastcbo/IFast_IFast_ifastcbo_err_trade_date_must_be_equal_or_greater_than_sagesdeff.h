#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_trade_date_must_be_equal_or_greater_than_sagesdeff : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_trade_date_must_be_equal_or_greater_than_sagesdeff() { }
		~CIFast_IFast_ifastcbo_err_trade_date_must_be_equal_or_greater_than_sagesdeff() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_TRADE_DATE_MUST_BE_EQUAL_OR_GREATER_THAN_SAGESDEFF")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Trade date must be equal or greater than 01Jan2013.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La date de transaction doit être égale ou ultérieure au 1er janvier 2013.")); }

        // Actions
	};
}



