#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_qesi_limit_exceeded : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_qesi_limit_exceeded() { }
		~CIFast_IFast_ifastcbo_warn_qesi_limit_exceeded() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_QESI_LIMIT_EXCEEDED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("QESI limit of %LIMIT_VALUE% has been exceeded.")); }

        // Actions
	};
}



