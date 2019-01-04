#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_trade_unit_adj_req_for_account_to : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_trade_unit_adj_req_for_account_to() { }
		~CIFast_IFast_ifastcbo_warn_trade_unit_adj_req_for_account_to() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_TRADE_UNIT_ADJ_REQ_FOR_ACCOUNT_TO")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Unit Adjustment required for Account To.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Unit Adjustment required for Account To.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Un ajustement d'unité est requis pour la cible du compte.")); }

        // Actions
	};
}



