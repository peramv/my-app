#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_warn_pending_trade_exists : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_warn_pending_trade_exists() { }
		~CIFast_IFast_ifastcbo_err_warn_pending_trade_exists() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_WARN_PENDING_TRADE_EXISTS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Pending Trade exists for this account.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Für dieses Konto existiert ein schwebender Handel.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Existe una operación pendiente para esta cuenta.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Il y a des transactions en suspens existantes au compte.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er bestaan in behandeling zijnde transacties voor dit account")); }

        // Actions
	};
}



