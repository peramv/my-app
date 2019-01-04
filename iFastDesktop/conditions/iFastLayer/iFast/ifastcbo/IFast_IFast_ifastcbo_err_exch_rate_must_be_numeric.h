#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_exch_rate_must_be_numeric : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_exch_rate_must_be_numeric() { }
		~CIFast_IFast_ifastcbo_err_exch_rate_must_be_numeric() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_EXCH_RATE_MUST_BE_NUMERIC")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Exchange rate must be a numeric value.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Wechselkurs muss nummerisch eingegeben werden")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El tipo de cambio debe ser un valor numérico")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le taux de change doit être une valeur numérique.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Wisselkoers moet in numerieke waarde worden uitgedrukt")); }

        // Actions
	};
}



