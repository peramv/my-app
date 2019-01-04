#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_didbrkr_didbrkr_redefine_repeats_not_allowed : public CConditionObject
	{
	public:
		CIFast_IFast_didbrkr_didbrkr_redefine_repeats_not_allowed() { }
		~CIFast_IFast_didbrkr_didbrkr_redefine_repeats_not_allowed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DIDBRKR_REDEFINE_REPEATS_NOT_ALLOWED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("didbrkr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Multiple Spousal contributor entities not allowed.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Multiple Spousal contributor entities not allowed.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Mehrere Objekte bei Ehelichem Beitragenden sind nicht erlaubt.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se permiten entidades de aportante conyugal múltiples.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les entités conjointes cotisantes multiples ne sont pas autorisées.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Meerdere eenheden voor echtelijke bijdrager zijn niet toegestaan")); }

        // Actions
	};
}



