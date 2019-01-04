#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_value_cannot_be_minus : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_value_cannot_be_minus() { }
		~CIFast_IFast_ifastcbo_err_value_cannot_be_minus() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_VALUE_CANNOT_BE_MINUS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Value cannot be minus.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Value cannot be minus.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La valeur ne peut être négative.")); }

        // Actions
	};
}



