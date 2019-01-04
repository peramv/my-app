#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_rif_invalid_rate_pud : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_rif_invalid_rate_pud() { }
		~CIFast_IFast_ifastcbo_err_rif_invalid_rate_pud() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_RIF_INVALID_RATE_PUD")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Valid values are only \"Percent\" or \"Dollar\".")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Valid values are only \"Percent\" or \"Dollar\".")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Gültige Werte sind nur \"Prozent\" oder \"Dollar\".")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Los únicos valores válidos son \"Por ciento\" o \"Dólar\".")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les seules valeurs valides sont Pourcentage ou Dollar.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Alleen 'Percentage' en 'Dollar' zijn geldige waarden")); }

        // Actions
	};
}



