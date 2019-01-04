#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_flatpecent_must_be_flat : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_flatpecent_must_be_flat() { }
		~CIFast_IFast_ifastcbo_err_flatpecent_must_be_flat() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FLATPECENT_MUST_BE_FLAT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Flat percent must be flat.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Vollständiger Prozent muss vollständig sein")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El porcentaje fijo debe ser fijo")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le pourcentage fixe doit être fixe.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Vast percentage moet vast zijn")); }

        // Actions
	};
}



