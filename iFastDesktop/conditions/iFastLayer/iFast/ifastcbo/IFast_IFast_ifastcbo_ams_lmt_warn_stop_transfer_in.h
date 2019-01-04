#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_ams_lmt_warn_stop_transfer_in : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_ams_lmt_warn_stop_transfer_in() { }
		~CIFast_IFast_ifastcbo_ams_lmt_warn_stop_transfer_in() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("AMS_LMT_WARN_STOP_TRANSFER_IN")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("AMS Code %CODE% has transfer in stop flag turned on.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("AMS Code %CODE% has transfer in stop flag turned on.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("AMS Code %CODE% has transfer in stop flag turned on.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le signal d'arrêt de transfert entrant du code de service de gestion de portefeuille %CODE% est activé.")); }

        // Actions
	};
}



