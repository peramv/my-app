#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_invalid_runmode : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_invalid_runmode() { }
		~CIFast_IFast_ifastdbrkr_err_invalid_runmode() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_RUNMODE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid Run Mode.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Ungültiger Laufmodus.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Modo de ejecución no válido.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Mode exécution invalide")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Ongeldige uitvoeringsmodus")); }

        // Actions
	};
}



