#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_trade_guar_adj_exists_after_trade_date_acct_to : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_trade_guar_adj_exists_after_trade_date_acct_to() { }
		~CIFast_IFast_ifastcbo_warn_trade_guar_adj_exists_after_trade_date_acct_to() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_TRADE_GUAR_ADJ_EXISTS_AFTER_TRADE_DATE_ACCT_TO")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Guarantee Adjustment exists after trade date for Account To.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Guarantee Adjustment exists after trade date for Account To.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Un ajustement de garantie existe après la date de transaction pour la cible du compte.")); }

        // Actions
	};
}



