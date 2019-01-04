#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_process_redemp_esop_particip : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_process_redemp_esop_particip() { }
		~CIFast_IFast_ifastdbrkr_err_process_redemp_esop_particip() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_PROCESS_REDEMP_ESOP_PARTICIP")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Processing Redemption from ESoP Participation Plan.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Tilgung vom EsoP-Beteiligungs-Plan wird verarbeitet")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Procesando rescate de plan de participación ESoP")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Traitement du rachat du régime de participation RADE")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Aflossing van ESoP Participation Plan wordt verwerkt")); }

        // Actions
	};
}



