#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_run_mode_invalid : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_run_mode_invalid() { }
		~CIFast_IFast_ifastdbrkr_err_run_mode_invalid() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_RUN_MODE_INVALID")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Run Mode not valid.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Run Mode not valid.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Laufmodus ungültig.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El modo de ejecución no es válido")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Mode exécution invalide")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Uitvoeringsmodus is niet geldig")); }

        // Actions
	};
}



