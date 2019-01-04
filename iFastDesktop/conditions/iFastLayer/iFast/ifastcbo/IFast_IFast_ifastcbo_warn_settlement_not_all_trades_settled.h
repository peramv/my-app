#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_settlement_not_all_trades_settled : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_settlement_not_all_trades_settled() { }
		~CIFast_IFast_ifastcbo_warn_settlement_not_all_trades_settled() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_SETTLEMENT_NOT_ALL_TRADES_SETTLED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Not all trades settled. See the Settlement screen for unsettled trades.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Not all trades settled. See the Settlement screen for unsettled trades.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Toutes les transactions ne sont pas réglées. Voir l'écran de règlement pour les transaction non réglées.")); }

        // Actions
	};
}



