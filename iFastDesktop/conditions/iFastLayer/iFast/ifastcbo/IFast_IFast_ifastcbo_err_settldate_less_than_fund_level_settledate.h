#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_Settledate_less_than_fund_level_Settledate : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_Settledate_less_than_fund_level_Settledate() { }
		~CIFast_IFast_ifastcbo_err_Settledate_less_than_fund_level_Settledate() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_SETTLEDATE_LESS_THAN_FUND_LEVEL_SETTLEDATE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("%SETTLEMENT_TYPE% is less than fund level %FUND_SETTLEMENT_TYPE% : %Short_SETTLEDATE%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La date de règlement est antérieure à la date de règlement au niveau du fonds: %Short_SETTLEDATE%.")); }

        // Actions
	};
}



