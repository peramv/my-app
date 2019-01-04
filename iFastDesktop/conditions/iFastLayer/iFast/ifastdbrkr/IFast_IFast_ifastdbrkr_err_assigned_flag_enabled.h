#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_assigned_flag_enabled : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_assigned_flag_enabled() { }
		~CIFast_IFast_ifastdbrkr_err_assigned_flag_enabled() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ASSIGNED_FLAG_ENABLED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Assigned Flag Enabled.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Zugewiesen-Kennzeichen aktiviert.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Flag asignado activado.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le signal de mise en garantie est désactivé.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Vlag voor toegewezen is ingeschakeld")); }

        // Actions
	};
}



