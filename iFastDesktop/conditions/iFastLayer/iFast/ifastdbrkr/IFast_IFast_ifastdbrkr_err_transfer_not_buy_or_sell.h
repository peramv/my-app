#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_transfer_not_buy_or_sell : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_transfer_not_buy_or_sell() { }
		~CIFast_IFast_ifastdbrkr_err_transfer_not_buy_or_sell() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_TRANSFER_NOT_BUY_OR_SELL")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Transfer is not a buy/sell.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Transfer ist kein Kauf/Verkauf")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La transferencia no es una compra/venta")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le transfert n'est pas Achat/Vente.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Overdracht is geen inkoop/verkoop")); }

        // Actions
	};
}



