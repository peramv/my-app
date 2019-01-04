#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_reg_agent_not_associated : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_reg_agent_not_associated() { }
		~CIFast_IFast_ifastcbo_err_reg_agent_not_associated() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_REG_AGENT_NOT_ASSOCIATED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Reg Agent Not associated with the Account")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'agent d'enregistrement n'est pas associé au compte.")); }

        // Actions
	};
}



