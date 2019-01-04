#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_info_service_agent_changed : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_info_service_agent_changed() { }
		~CIFast_IFast_ifastcbo_info_service_agent_changed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("INFO_SERVICE_AGENT_CHANGED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 4; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Service Agent already changed by Compensation Agent.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'agent de service a déjà été changé par l'agent de commission.")); }

        // Actions
	};
}



