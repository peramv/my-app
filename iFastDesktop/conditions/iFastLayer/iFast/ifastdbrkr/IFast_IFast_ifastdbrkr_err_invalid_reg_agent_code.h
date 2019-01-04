#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_invalid_reg_agent_code : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_invalid_reg_agent_code() { }
		~CIFast_IFast_ifastdbrkr_err_invalid_reg_agent_code() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_REG_AGENT_CODE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Registration Agent Code is invalid.Please re-enter")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le code de l'agent d'enregistrement est invalide. Veuillez le saisir à nouveau.")); }

        // Actions
	};
}



