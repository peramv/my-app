#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_ams_lmt_warn_stop_redemption : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_ams_lmt_warn_stop_redemption() { }
		~CIFast_IFast_ifastcbo_ams_lmt_warn_stop_redemption() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("AMS_LMT_WARN_STOP_REDEMPTION")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("AMS Code %CODE% has redemption stop flag turned on.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("AMS Code %CODE% has redemption stop flag turned on.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("AMS Code %CODE% has redemption stop flag turned on.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le signal d'arrêt de rachat du code de service de gestion de portefeuille %CODE% est activé.")); }

        // Actions
	};
}



