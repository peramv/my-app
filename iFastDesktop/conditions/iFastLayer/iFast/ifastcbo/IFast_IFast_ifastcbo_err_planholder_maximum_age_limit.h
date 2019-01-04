#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_planholder_maximum_age_limit : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_planholder_maximum_age_limit() { }
		~CIFast_IFast_ifastcbo_err_planholder_maximum_age_limit() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_PLANHOLDER_MAXIMUM_AGE_LIMIT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Planholder exceeds the maximum age limit to hold for this particular registered account.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Planinhaber entspricht nicht den Anforderungen an das maximale Alter für dieses spezielle Auslandskonto.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El titular del plan supera la edad máxima permitida para esta cuenta registrada en particular.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le titulaire du régime excède la limite d'âge maximal pour ce compte enregistré particulier.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Planhouder overschrijdt de maximumleeftijd om houder te zijn van dit specifieke geregistreerde account")); }

        // Actions
	};
}



