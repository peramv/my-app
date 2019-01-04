#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastbp_err_family_code_or_name_not_existing : public CConditionObject
	{
	public:
		CIFast_IFast_ifastbp_err_family_code_or_name_not_existing() { }
		~CIFast_IFast_ifastbp_err_family_code_or_name_not_existing() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FAMILY_CODE_OR_NAME_NOT_EXISTING")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastbp")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Family code is not existing.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Code de famille inexistant")); }

        // Actions
	};
}



