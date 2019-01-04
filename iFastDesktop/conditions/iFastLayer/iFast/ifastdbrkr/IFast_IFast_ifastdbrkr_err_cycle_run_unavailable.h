#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_cycle_run_unavailable : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_cycle_run_unavailable() { }
		~CIFast_IFast_ifastdbrkr_err_cycle_run_unavailable() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_CYCLE_RUN_UNAVAILABLE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Cycle-Run record not available.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Cycle-Run record not available.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Cycle-Run-Eintrag nicht verfügbar.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El registro Cycle-Run no está disponible")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'enregistrement d'exécution du cycle n'est pas disponible.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Record Cyclus-uitvoering is niet beschikbaar")); }

        // Actions
	};
}



