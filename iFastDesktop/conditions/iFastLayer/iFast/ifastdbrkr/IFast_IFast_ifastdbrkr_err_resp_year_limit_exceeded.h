#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_resp_year_limit_exceeded : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_resp_year_limit_exceeded() { }
		~CIFast_IFast_ifastdbrkr_err_resp_year_limit_exceeded() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_RESP_YEAR_LIMIT_EXCEEDED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("RESP Year Limit for %BENNAME% is exceeded. Annual Contribution Limit %ANNUALLIMIT% exceeded. Annual Contribution to date is %TODATE%.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("RESP-Jahresgrenze überschritten.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Se ha excedido el límite anual para RESP.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Plafond annuel REEE excédé")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Jaargrens RESP is overschreden")); }

        // Actions
	};
}



