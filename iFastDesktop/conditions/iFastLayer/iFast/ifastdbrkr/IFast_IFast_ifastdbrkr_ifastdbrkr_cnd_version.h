#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_ifastdbrkr_cnd_version : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_ifastdbrkr_cnd_version() { }
		~CIFast_IFast_ifastdbrkr_ifastdbrkr_cnd_version() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("IFASTDBRKR_CND_VERSION")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 4; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Dev")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Dev")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Dev")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Dev")); }

        // Actions
	};
}



