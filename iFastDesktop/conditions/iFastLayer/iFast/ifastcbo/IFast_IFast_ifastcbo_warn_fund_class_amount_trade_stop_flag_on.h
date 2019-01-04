#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_fund_class_amount_trade_stop_flag_on : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_fund_class_amount_trade_stop_flag_on() { }
		~CIFast_IFast_ifastcbo_warn_fund_class_amount_trade_stop_flag_on() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_FUND_CLASS_AMOUNT_TRADE_STOP_FLAG_ON")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Amount orders are not allowed for %FUND% and %CLASS%")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les ordres de montant ne sont pas autorisés pour le fonds %FUND% et la classe %CLASS%.")); }

        // Actions
	};
}



