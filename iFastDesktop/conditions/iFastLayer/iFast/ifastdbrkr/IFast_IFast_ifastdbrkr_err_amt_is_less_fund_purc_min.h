#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_amt_is_less_fund_purc_min : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_amt_is_less_fund_purc_min() { }
		~CIFast_IFast_ifastdbrkr_err_amt_is_less_fund_purc_min() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_AMT_IS_LESS_FUND_PURC_MIN")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Amount is less than Fund Purchase minimum.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Betrag kann unter dem minimalen Fonds-Kauf liegen")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El monto es inferior al mínimo de compra del fondo")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le montant est inférieur au minimum d'achat de fonds.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Bedrag is lager dan minimum fondsaankoop")); }

        // Actions
	};
}



