#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_reg_agent_tax_type : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_reg_agent_tax_type() { }
		~CIFast_IFast_ifastcbo_err_reg_agent_tax_type() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_REG_AGENT_TAX_TYPE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Tax Type is Required for Registration Agent")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le type d'impôt est requis pour l'enregistrement de l'agent.")); }

        // Actions
	};
}



