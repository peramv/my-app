#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_service_agent_must_be_changed : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_service_agent_must_be_changed() { }
		~CIFast_IFast_ifastcbo_err_service_agent_must_be_changed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_SERVICE_AGENT_MUST_BE_CHANGED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The Service Agent must be changed before changing the Compensation Agent.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'agent de service doit être changé avant l'agent de commission.")); }

        // Actions
	};
}



