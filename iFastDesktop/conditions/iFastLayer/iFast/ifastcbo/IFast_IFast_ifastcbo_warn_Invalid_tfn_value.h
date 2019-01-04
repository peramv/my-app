#pragma once

#include "ConditionObject.h"

namespace CND
{
		class CIFast_IFast_ifastcbo_warn_Invalid_tfn_value: public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_Invalid_tfn_value() { }
		~CIFast_IFast_ifastcbo_warn_Invalid_tfn_value() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_INVALID_TFN_VALUE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid TFN value.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Invalid TFN value.")); }

        // Actions
	};
}



