#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_trade_not_allowed_to_cancel : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_trade_not_allowed_to_cancel() { }
		~CIFast_IFast_ifastcbo_err_trade_not_allowed_to_cancel() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_TRADE_NOT_ALLOWED_TO_CANCEL")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("BackDate: Cancel all transactions on after %TRADE_DATE% or change tradedate")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Antidatage : annuler toutes les transactions après la date du %TRADE_DATE% ou changer la date de transaction.")); }

        // Actions
	};
}



