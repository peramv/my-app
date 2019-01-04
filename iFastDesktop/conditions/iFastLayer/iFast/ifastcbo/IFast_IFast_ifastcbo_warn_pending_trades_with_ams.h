#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_pending_trades_with_ams : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_pending_trades_with_ams() { }
		~CIFast_IFast_ifastcbo_warn_pending_trades_with_ams() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_PENDING_TRADES_WITH_AMS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Accounts with pending trades are not eligible for AMS rebalancing.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Accounts with pending trades are not eligible for AMS rebalancing.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Accounts with pending trades are not eligible for AMS rebalancing.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les comptes comportant des transactions en suspens ne sont pas admissibles pour le rebalancement de service de gestion de portefeuille.")); }

        // Actions
	};
}



