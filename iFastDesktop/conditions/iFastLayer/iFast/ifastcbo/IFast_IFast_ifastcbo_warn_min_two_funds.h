#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_min_two_funds : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_min_two_funds() { }
		~CIFast_IFast_ifastcbo_warn_min_two_funds() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_MIN_TWO_FUNDS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Minimum two funds should be part of the mix.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Au moins deux fonds devraient faire partie de la composition.")); }

        // Actions
	};
}



