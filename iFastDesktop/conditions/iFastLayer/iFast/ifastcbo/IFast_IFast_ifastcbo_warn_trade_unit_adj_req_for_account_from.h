#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_trade_unit_adj_req_for_account_from : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_trade_unit_adj_req_for_account_from() { }
		~CIFast_IFast_ifastcbo_warn_trade_unit_adj_req_for_account_from() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_TRADE_UNIT_ADJ_REQ_FOR_ACCOUNT_FROM")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Unit Adjustment required for Account From.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Unit Adjustment required for Account From.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Un ajustement d'unité est requis pour l'origine du compte.")); }

        // Actions
	};
}



