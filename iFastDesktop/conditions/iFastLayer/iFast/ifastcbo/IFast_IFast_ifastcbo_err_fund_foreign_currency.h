#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_fund_foreign_currency : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_fund_foreign_currency() { }
		~CIFast_IFast_ifastcbo_err_fund_foreign_currency() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FUND_FOREIGN_CURRENCY")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The fund class currency must be the same as system currency.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("The fund class currency must be the same as system currency.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("The fund class currency must be the same as system currency.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La monnaie de la classe du fonds doit être la même que la monnaie du système.")); }

        // Actions
	};
}



