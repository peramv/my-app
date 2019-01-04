#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_multiple_registration_agent_entities : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_multiple_registration_agent_entities() { }
		~CIFast_IFast_ifastcbo_err_multiple_registration_agent_entities() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_MULTIPLE_REGISTRATION_AGENT_ENTITIES")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Multiple Registration Agent Entities not allowed.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Multiples entités agent d'enregistrement non autorisées")); }

        // Actions
	};
}



