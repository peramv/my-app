#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_flat_percent_must_be_yes : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_flat_percent_must_be_yes() { }
		~CIFast_IFast_ifastcbo_err_flat_percent_must_be_yes() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FLAT_PERCENT_MUST_BE_YES")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Flat Percent must be yes.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Ganzzahliger Prozentsatz muss Ja sein")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El porcentaje fijo debe ser Sí.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le pourcentage fixe doit être activé.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Vast percentage moet ja zijn")); }

        // Actions
	};
}



