#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_trade_date_required : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_trade_date_required() { }
		~CIFast_IFast_ifastdbrkr_err_trade_date_required() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_TRADE_DATE_REQUIRED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Trade Date must be entered.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Trade Date must be entered.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La date de transaction est requise.")); }

        // Actions
	};
}



