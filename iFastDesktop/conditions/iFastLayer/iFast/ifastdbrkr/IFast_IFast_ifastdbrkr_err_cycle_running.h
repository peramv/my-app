#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_cycle_running : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_cycle_running() { }
		~CIFast_IFast_ifastdbrkr_err_cycle_running() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_CYCLE_RUNNING")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Unable to proceed, cycle is running.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Fortfahren nicht möglich, Zyklus läuft.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Imposible continuar, el ciclo se está ejecutando.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Impossible de procéder, le cycle est en cours.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Verwerking is niet mogelijk, cyclus wordt uitgevoerd")); }

        // Actions
	};
}



