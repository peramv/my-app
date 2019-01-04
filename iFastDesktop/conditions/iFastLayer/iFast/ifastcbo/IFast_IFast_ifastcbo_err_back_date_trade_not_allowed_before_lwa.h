#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_back_date_trade_not_allowed_before_lwa : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_back_date_trade_not_allowed_before_lwa() { }
		~CIFast_IFast_ifastcbo_err_back_date_trade_not_allowed_before_lwa() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_BACK_DATE_TRADE_NOT_ALLOWED_BEFORE_LWA")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Cannot backdate trades before LWA Option")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Impossible d'antidater des transactions avant l'option MRV.")); }

        // Actions
	};
}



