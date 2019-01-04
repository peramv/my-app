#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_gi_selected_amount_not_trade_amount : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_gi_selected_amount_not_trade_amount() { }
		~CIFast_IFast_ifastcbo_err_gi_selected_amount_not_trade_amount() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_GI_SELECTED_AMOUNT_NOT_TRADE_AMOUNT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Selected amount is different than the trade amount.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le montant sélectionné est différent du montant de la transaction.")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Please correct.")); }
	};
}



