#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_stop_money_in_for_tax_type : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_stop_money_in_for_tax_type() { }
		~CIFast_IFast_ifastcbo_err_stop_money_in_for_tax_type() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_STOP_MONEY_IN_FOR_TAX_TYPE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("New money-in for %VAR1%  is not allowed after %GRANDFATHEREDDATE%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Une nouvelle entrée d'argent pour %VAR1% n'est pas autorisée après le %GRANDFATHEREDDATE%.")); }

        // Actions
	};
}



