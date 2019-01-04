#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_unsettle_cannot_cancel_for_dividend_fund : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_unsettle_cannot_cancel_for_dividend_fund() { }
		~CIFast_IFast_ifastdbrkr_err_unsettle_cannot_cancel_for_dividend_fund() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_UNSETTLE_CANNOT_CANCEL_FOR_DIVIDEND_FUND")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Unsettled trades cannot be cancelled for funds that pay dividends on redemption or fund close.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Unsettled trades cannot be cancelled for funds that pay dividends on redemption or fund close.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les transactions non réglées ne peuvent être supprimées pour un fonds qui exige le paiement de dividendes, un rachat ou une fermeture de fonds.")); }

        // Actions
	};
}



