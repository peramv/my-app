#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_redemp_stop_flag_enabled : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_redemp_stop_flag_enabled() { }
		~CIFast_IFast_ifastdbrkr_err_redemp_stop_flag_enabled() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_REDEMP_STOP_FLAG_ENABLED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Redemption Stop Flag Enabled.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Kennzeichen für Stopp der Tilgung aktiviert.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Flag de detención de rescate activado.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le signal de rachat est désactivé.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Vlag voor einde aflossing is ingeschakeld")); }

        // Actions
	};
}



