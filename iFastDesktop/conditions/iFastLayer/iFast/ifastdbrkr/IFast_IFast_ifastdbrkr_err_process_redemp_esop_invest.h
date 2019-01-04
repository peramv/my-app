#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_process_redemp_esop_invest : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_process_redemp_esop_invest() { }
		~CIFast_IFast_ifastdbrkr_err_process_redemp_esop_invest() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_PROCESS_REDEMP_ESOP_INVEST")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Processing Redemption from ESoP Investment Plan.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Tilgung vom EsoP-Investment-Plan wird verarbeitet")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Procesando rescate de plan de inversión ESoP")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Traitement du rachat du régime de placement RADE")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Aflossing van ESoP Investment Plan wordt verwerkt")); }

        // Actions
	};
}



