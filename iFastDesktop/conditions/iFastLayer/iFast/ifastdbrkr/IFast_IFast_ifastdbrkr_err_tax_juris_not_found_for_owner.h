#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_tax_juris_not_found_for_owner : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_tax_juris_not_found_for_owner() { }
		~CIFast_IFast_ifastdbrkr_err_tax_juris_not_found_for_owner() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_TAX_JURIS_NOT_FOUND_FOR_OWNER")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Tax Jurisdiction not found for owner.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Juridiction fiscale introuvable pour le titulaire")); }

        // Actions
	};
}



