#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_pension_sex_prcnt_not_add_to_100 : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_pension_sex_prcnt_not_add_to_100() { }
		~CIFast_IFast_ifastcbo_err_pension_sex_prcnt_not_add_to_100() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_PENSION_SEX_PRCNT_NOT_ADD_TO_100")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Unisex/Sex Distinct Percents must add up to 100.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Unisex/ Geschlechtertrennungs-Prozent müssen zusammen 100 ergeben.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Los porcentajes unisex/sexo diferente deben sumar 100.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les pourcentages avec ou sans distinction de sexe doivent totaliser 100 %.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Percentages zonder/met sekseonderscheid moeten in totaal 100 zijn")); }

        // Actions
	};
}



