#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_rdsp_trade_date_after_beneficiary_date_of_death : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_rdsp_trade_date_after_beneficiary_date_of_death() { }
		~CIFast_IFast_ifastcbo_warn_rdsp_trade_date_after_beneficiary_date_of_death() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_RDSP_TRADE_DATE_AFTER_BENEFICIARY_DATE_OF_DEATH")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Trade date is after Beneficiary's Date of Death.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Trade date is after Beneficiary's Date of Death.")); }

        // Actions
	};
}



