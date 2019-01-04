#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_Settledays_less_than_fund_level_Settledays : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_Settledays_less_than_fund_level_Settledays() { }
		~CIFast_IFast_ifastcbo_warn_Settledays_less_than_fund_level_Settledays() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_SETTLEDAYS_LESS_THAN_FUND_LEVEL_SETTLEDAYS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Settle days is less than fund level settle days: %Short_SETTLEDAYS%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La valeur de jours de règlement est inférieure à la valeur au niveau du fonds: %Short_SETTLEDAYS%.")); }

        // Actions
	};
}



