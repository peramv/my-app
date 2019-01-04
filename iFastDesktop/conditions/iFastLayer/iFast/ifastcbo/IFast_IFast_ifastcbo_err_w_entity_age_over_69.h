#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_w_entity_age_over_69 : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_w_entity_age_over_69() { }
		~CIFast_IFast_ifastcbo_err_w_entity_age_over_69() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_W_ENTITY_AGE_OVER_69")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Tax Type %RRSPLIRA% restricts entity to under 71 years of age.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Steuerart %RRSPLIRA% beschränkt auf Objekte unter 71 Jahren.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El tipo tributario %RRSPLIRA% restringe la entidad a menos de 71 años de edad.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le type d'imposition %RRSPLIRA% restreint l'entité à un âge de moins de 71 ans.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Voor belastingtype %RRSPLIRA% moet de eenheid minder dan 71 jaar oud zijn")); }

        // Actions
	};
}



