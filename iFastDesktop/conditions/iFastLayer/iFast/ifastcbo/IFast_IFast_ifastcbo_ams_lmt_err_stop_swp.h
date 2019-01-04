#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_ams_lmt_err_stop_swp : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_ams_lmt_err_stop_swp() { }
		~CIFast_IFast_ifastcbo_ams_lmt_err_stop_swp() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("AMS_LMT_ERR_STOP_SWP")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("AMS Code %CODE% has SWP stop flag turned on.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("AMS Code %CODE% has SWP stop flag turned on.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("AMS Code %CODE% has SWP stop flag turned on.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le signal d'arrêt de PRP du code SGP %CODE% est activé.")); }

        // Actions
	};
}



