#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_ifastcbo_err_fund_not_rrif_eligible : public CConditionObject
	{
	public:
		CIFast_Infrastructure_ifastcbo_err_fund_not_rrif_eligible() { }
		~CIFast_Infrastructure_ifastcbo_err_fund_not_rrif_eligible() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FUND_NOT_RRIF_ELIGIBLE")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Field %FIELD% has not been validated.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Field '^' has not been validated.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Feld %FIELD% wurde nicht gültig gesetzt.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se ha validado el campo %FIELD%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le champ %FIELD% n'a pas été validé.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Veld %FIELD% is niet gevalideerd")); }

        // Actions
	};
}



