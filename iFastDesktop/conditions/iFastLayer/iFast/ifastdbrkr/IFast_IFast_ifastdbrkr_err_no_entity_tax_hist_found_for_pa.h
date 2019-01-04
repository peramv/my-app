#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_no_entity_tax_hist_found_for_pa : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_no_entity_tax_hist_found_for_pa() { }
		~CIFast_IFast_ifastdbrkr_err_no_entity_tax_hist_found_for_pa() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NO_ENTITY_TAX_HIST_FOUND_FOR_PA")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Tax Jurisdiction not found for Paying Agent.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Juridiction fiscale introuvable pour l'agent payeur")); }

        // Actions
	};
}



