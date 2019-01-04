#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_percentage_holdings_not_more_than_100 : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_percentage_holdings_not_more_than_100() { }
		~CIFast_IFast_ifastcbo_err_percentage_holdings_not_more_than_100() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_PERCENTAGE_HOLDINGS_NOT_MORE_THAN_100")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Percentage holdings not more than 100.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Prozentsatz Beteiligung nicht mehr als 100")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Las tenencias porcentuales no son más de 100")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le pourcentage du portefeuille ne doit pas excéder 100 %.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Percentage vermogens is niet meer dan 100")); }

        // Actions
	};
}



