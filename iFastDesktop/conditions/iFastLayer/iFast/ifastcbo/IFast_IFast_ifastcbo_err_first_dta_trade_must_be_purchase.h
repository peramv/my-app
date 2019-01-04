#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_first_dta_trade_must_be_purchase : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_first_dta_trade_must_be_purchase() { }
		~CIFast_IFast_ifastcbo_err_first_dta_trade_must_be_purchase() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FIRST_DTA_TRADE_MUST_BE_PURCHASE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The first direct trading for an account must be purchase.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("The first direct trading for an account must be purchase.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("The first direct trading for an account must be purchase.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La première opération directe d'un compte doit être un achat.")); }

        // Actions
	};
}



