#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_pension_distinctsex_percent_must_eq_100 : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_pension_distinctsex_percent_must_eq_100() { }
		~CIFast_IFast_ifastcbo_err_pension_distinctsex_percent_must_eq_100() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_PENSION_DISTINCTSEX_PERCENT_MUST_EQ_100")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Sex Distinct Percent must be 100%. Tax Jurisdiction never allowed Unisex.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Geschlechtertrennungs-Prozent muss 100% sein. Steuer-Rechtssprechung erlaubt Unisex nicht.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El porcentaje de sexo distinto debe ser 100%. Tax Jurisdiction never allowed Unisex.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le pourcentage avec distinction de sexe doit être de 100 %. L'absence de distinction de sexe n'a jamais été autorisé par la juridiction fiscale.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Percentage met sekseonderscheid moet 100% zijn. Zonder sekseonderscheid is nooit toegestaan in belastingrechtsgebied")); }

        // Actions
	};
}



