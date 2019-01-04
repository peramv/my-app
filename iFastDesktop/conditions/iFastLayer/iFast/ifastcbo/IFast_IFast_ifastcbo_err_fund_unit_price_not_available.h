#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_fund_unit_price_not_available : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_fund_unit_price_not_available() { }
		~CIFast_IFast_ifastcbo_err_fund_unit_price_not_available() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FUND_UNIT_PRICE_NOT_AVAILABLE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Unit price is not available for this fund.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Unit price is not available for this fund.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Unit price is not available for this fund.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le prix unitaire n'est pas disponible pour ce fonds.")); }

        // Actions
	};
}



