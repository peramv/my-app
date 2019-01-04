#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_invalid_nric : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_invalid_nric() { }
		~CIFast_IFast_ifastcbo_warn_invalid_nric() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_INVALID_NRIC")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid NRIC")); }

        // Actions
	};
}



