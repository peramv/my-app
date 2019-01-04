#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_info_sages_uc_reason : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_info_sages_uc_reason() { }
		~CIFast_IFast_ifastcbo_info_sages_uc_reason() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("INFO_SAGES_UC_REASON")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 4; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("%SAGES_UC_REASON%")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("%SAGES_UC_REASON%")); }

        // Actions
	};
}



