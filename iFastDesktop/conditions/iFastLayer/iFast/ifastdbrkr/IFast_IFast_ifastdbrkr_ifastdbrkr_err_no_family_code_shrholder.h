#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_ifastdbrkr_err_no_family_code_shrholder : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_ifastdbrkr_err_no_family_code_shrholder() { }
		~CIFast_IFast_ifastdbrkr_ifastdbrkr_err_no_family_code_shrholder() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("IFASTDBRKR_ERR_NO_FAMILY_CODE_SHRHOLDER")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("No Family Code for Shareholder.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("No Family Code for Shareholder.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Aucun code de famille pour l'actionnaire")); }

        // Actions
	};
}



