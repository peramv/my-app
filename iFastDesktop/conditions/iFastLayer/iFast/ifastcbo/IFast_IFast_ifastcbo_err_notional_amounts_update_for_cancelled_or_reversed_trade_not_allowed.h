#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_notional_amounts_update_for_cancelled_or_reversed_trade_not_allowed : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_notional_amounts_update_for_cancelled_or_reversed_trade_not_allowed() { }
		~CIFast_IFast_ifastcbo_err_notional_amounts_update_for_cancelled_or_reversed_trade_not_allowed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NOTIONAL_AMOUNTS_UPDATE_FOR_CANCELLED_OR_REVERSED_TRADE_NOT_ALLOWED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Update of transfer notional values for a cancelled and/or reversed trade is not allowed.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La mise à jour des valeurs notionnelles de transfert d’une transaction contrepassée ou annulée n'est pas autorisée.")); }		

        // Actions
	};
}



