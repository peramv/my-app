#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_fund_class_not_in_portfolio : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_fund_class_not_in_portfolio() { }
		~CIFast_IFast_ifastcbo_err_fund_class_not_in_portfolio() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FUND_CLASS_NOT_IN_PORTFOLIO")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Excess foreign fund/class not in portfolio.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Excess foreign fund/class not in portfolio.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Excess foreign fund/class not in portfolio.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le fonds/la classe de l'excédent étranger n'est pas dans le portefeuille.")); }

        // Actions
	};
}



