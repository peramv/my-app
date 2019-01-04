#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_acct_categ_nav_share_lots_deleted_pending_trades_exist : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_acct_categ_nav_share_lots_deleted_pending_trades_exist() { }
		~CIFast_IFast_ifastcbo_warn_acct_categ_nav_share_lots_deleted_pending_trades_exist() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_ACCT_CATEG_NAV_SHARE_LOTS_DELETED_PENDING_TRADES_EXIST")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Nav Share lots Account Category deleted. Pending Trades exist.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Nav Share lots Account Category deleted. Pending Trades exist.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La catégorie de compte des lots de parts à la valeur de l'actif net est supprimée. Des transactions en suspens existent.")); }

        // Actions
	};
}



