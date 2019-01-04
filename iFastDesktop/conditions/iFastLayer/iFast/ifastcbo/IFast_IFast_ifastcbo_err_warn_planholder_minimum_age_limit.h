#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_warn_planholder_minimum_age_limit : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_warn_planholder_minimum_age_limit() { }
		~CIFast_IFast_ifastcbo_err_warn_planholder_minimum_age_limit() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_WARN_PLANHOLDER_MINIMUM_AGE_LIMIT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Planholder does not meet the minimum age requirements for this particular registered account.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Planinhaber entspricht nicht den Anforderungen an das minimale Alter für dieses spezielle Auslandskonto.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El titular del plan no cumple con la edad mínima requerida para esta cuenta registrada en particular.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le titulaire du régime ne répond pas aux exigences d'âge minimal pour ce compte enregistré particulier.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Planhouder voldoet niet aan de eisen voor de minimumleeftijd voor dit specifieke geregistreerde account")); }

        // Actions
	};
}



