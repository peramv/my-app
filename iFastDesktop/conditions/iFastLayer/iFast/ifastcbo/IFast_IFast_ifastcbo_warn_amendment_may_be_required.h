#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_amendment_may_be_required : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_amendment_may_be_required() { }
		~CIFast_IFast_ifastcbo_warn_amendment_may_be_required() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_AMENDMENT_MAY_BE_REQUIRED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Amendment may be required.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Une modification pourrait être requise.")); }

        // Actions
	};
}



