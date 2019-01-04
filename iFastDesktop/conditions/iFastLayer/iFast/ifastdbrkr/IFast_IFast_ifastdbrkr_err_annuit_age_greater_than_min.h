#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_annuit_age_greater_than_min : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_annuit_age_greater_than_min() { }
		~CIFast_IFast_ifastdbrkr_err_annuit_age_greater_than_min() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ANNUIT_AGE_GREATER_THAN_MIN")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Annuitant age greater than maximum age allowed.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Das Alter des Rentenempfängers liegt über dem maximal erlaubten Alter")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La edad del titular de la anualidad excede la edad permitida")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'âge du crédirentier est supérieur à l'âge maximal autorisé.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Leeftijd lijfrentetrekker is hoger dan de maximaal toegestane leeftijd")); }

        // Actions
	};
}



