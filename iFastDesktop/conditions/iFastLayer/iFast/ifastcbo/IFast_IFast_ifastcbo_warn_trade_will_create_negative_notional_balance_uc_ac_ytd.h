#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_trade_will_create_negative_notional_balance_uc_ac_ytd : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_trade_will_create_negative_notional_balance_uc_ac_ytd() { }
		~CIFast_IFast_ifastcbo_warn_trade_will_create_negative_notional_balance_uc_ac_ytd() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_TRADE_WILL_CREATE_NEGATIVE_NOTIONAL_BALANCE_UC_AC_YTD")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Trade will create negative notional balance in UC, AC or YTD Amount.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La transaction créera un solde notionnel négatif en cumul annuel pour les montants de CNS et de CS.")); }

        // Actions
	};
}



