#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_invalid_tax_type4_regagent : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_invalid_tax_type4_regagent() { }
		~CIFast_IFast_ifastcbo_err_invalid_tax_type4_regagent() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_TAX_TYPE4_REGAGENT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Account Tax Type not valid to redirect to Reg Agent")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le type d'impôt du compte est invalide pour le réacheminement vers l'agent d'enregistrement.")); }

        // Actions
	};
}



