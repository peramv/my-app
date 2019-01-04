#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_percentage_holdings_over_100 : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_percentage_holdings_over_100() { }
		~CIFast_IFast_ifastcbo_err_percentage_holdings_over_100() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_PERCENTAGE_HOLDINGS_OVER_100")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Percentage of holdings over 100%.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Prozentsatz der Beteiligungen über 100%")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El porcentaje de las tenencias suma más de 100%")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le pourcentage du portefeuille excède 100 %.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Percentage vermogens is meer dan 100%")); }

        // Actions
	};
}



