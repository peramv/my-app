#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_invalid_value_for_parent_legal_guardian : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_invalid_value_for_parent_legal_guardian() { }
		~CIFast_IFast_ifastcbo_err_invalid_value_for_parent_legal_guardian() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_VALUE_FOR_PARENT_LEGAL_GUARDIAN")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid value for Parent\\Legal Guardian.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La valeur de parent/tuteur légal est invalide.")); }

        // Actions
	};
}



