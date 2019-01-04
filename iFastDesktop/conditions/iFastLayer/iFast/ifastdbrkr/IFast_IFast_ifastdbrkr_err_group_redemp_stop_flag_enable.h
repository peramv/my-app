#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_group_redemp_stop_flag_enable : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_group_redemp_stop_flag_enable() { }
		~CIFast_IFast_ifastdbrkr_err_group_redemp_stop_flag_enable() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_GROUP_REDEMP_STOP_FLAG_ENABLE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Group Redemption Stop Flag Enabled.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Kennzeichen für Stopp der Gruppentilgung aktiviert.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Flag de detención de rescate de grupo activado.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le signal de rachat du groupe est désactivé.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Vlag voor einde groepsaflossing is ingeschakeld")); }

        // Actions
	};
}



