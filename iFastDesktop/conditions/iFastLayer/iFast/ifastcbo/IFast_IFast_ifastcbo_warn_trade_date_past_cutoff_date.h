#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_trade_date_past_cutoff_date : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_trade_date_past_cutoff_date() { }
		~CIFast_IFast_ifastcbo_warn_trade_date_past_cutoff_date() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_TRADE_DATE_PAST_CUTOFF_DATE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Trade date is past client cut-off time.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Trade date is past client cut-off time.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La transaction a dépassé l'heure limite du client.")); }

        // Actions
	};
}



