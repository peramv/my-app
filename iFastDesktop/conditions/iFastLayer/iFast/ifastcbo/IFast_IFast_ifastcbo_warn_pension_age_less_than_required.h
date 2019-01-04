#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_pension_age_less_than_required : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_pension_age_less_than_required() { }
		~CIFast_IFast_ifastcbo_warn_pension_age_less_than_required() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_PENSION_AGE_LESS_THAN_REQUIRED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Minimum withdrawal age is less than required for the Tax Type and Pension Jurisdiction.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Minimales Abhebe-Alter liegt unter dem für die Steuerart und die Renten-Rechtssprechung erforderlichen.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La edad de retiro mínima es inferior a la requerida para el tipo tributario y jurisdicción de jubilación.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'âge de retrait minimal est inférieur à l'âge requis pour le type d'imposition et la juridiction de retraire.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Minimum opnameleeftijd is lager dan vereist voor het belastingtype en het pensioenrechtsgebied")); }

        // Actions
	};
}



