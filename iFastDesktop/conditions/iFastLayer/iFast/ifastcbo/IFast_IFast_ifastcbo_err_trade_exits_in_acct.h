#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_trade_exits_in_acct : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_trade_exits_in_acct() { }
		~CIFast_IFast_ifastcbo_err_trade_exits_in_acct() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_TRADE_EXITS_IN_ACCT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("There are subsequent trades in the account which must be cancelled before proceeding.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Vous devez annuler les transactions subséquentes du compte avant d’effectuer cette opération.")); }

        // Actions
	};
}



