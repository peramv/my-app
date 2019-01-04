#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_rdsp_api_timeout : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_rdsp_api_timeout() { }
		~CIFast_IFast_ifastcbo_warn_rdsp_api_timeout() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_RDSP_API_TIMEOUT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("RDSP Internal Error - Please contact API owner.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("RDSP Internal Error - Please contact API owner.")); }

        // Actions
	};
}



