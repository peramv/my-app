#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_amt_may_less_fund_purc_min : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_amt_may_less_fund_purc_min() { }
		~CIFast_IFast_ifastdbrkr_err_amt_may_less_fund_purc_min() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_AMT_MAY_LESS_FUND_PURC_MIN")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Amount may be less than fund purchase minimum.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Betrag kann unter dem minimalen Fonds-Kauf liegen")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El monto puede ser inferior al mínimo de compra del fondo")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le montant peut être inférieur au minimum d'achat de fonds.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Bedrag kan lager zijn dan minimum fondsaankoop")); }

        // Actions
	};
}



