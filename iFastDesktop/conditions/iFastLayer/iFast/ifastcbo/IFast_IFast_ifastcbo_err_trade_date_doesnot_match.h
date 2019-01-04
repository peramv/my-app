#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_trade_date_doesnot_match : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_trade_date_doesnot_match() { }
		~CIFast_IFast_ifastcbo_err_trade_date_doesnot_match() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_TRADE_DATE_DOESNOT_MATCH")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Trade date does not match the aggregated order.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Trade date does not match the aggregated order.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La date de transaction ne correspond pas à l'ordre global.")); }

        // Actions
	};
}



