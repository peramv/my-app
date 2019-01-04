#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_invalid_associated_accnum : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_invalid_associated_accnum() { }
		~CIFast_IFast_ifastdbrkr_err_invalid_associated_accnum() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_ASSOCIATED_ACCNUM")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid associated account number.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Numéro de compte associé invalide")); }

        // Actions
	};
}



