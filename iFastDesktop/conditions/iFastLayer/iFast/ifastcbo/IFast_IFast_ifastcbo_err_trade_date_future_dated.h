#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_trade_date_future_dated : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_trade_date_future_dated() { }
		~CIFast_IFast_ifastcbo_err_trade_date_future_dated() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_TRADE_DATE_FUTURE_DATED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Future trade date is not allowed.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Future trade date is not allowed.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Future trade date is not allowed.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Une date de transaction postérieure à la date actuelle n'est pas autorisée.")); }

        // Actions
	};
}



