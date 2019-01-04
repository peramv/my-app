#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_redirect_to_reg_agent_not_allowed : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_redirect_to_reg_agent_not_allowed() { }
		~CIFast_IFast_ifastcbo_err_redirect_to_reg_agent_not_allowed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_REDIRECT_TO_REG_AGENT_NOT_ALLOWED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Redirect to Reg Agent option Not allowed for the trade")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'option de réacheminement vers l'agent d'enregistrement n'est pas autorisée pour la transaction.")); }

        // Actions
	};
}



