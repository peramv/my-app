#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_different_reg_agent : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_different_reg_agent() { }
		~CIFast_IFast_ifastcbo_warn_different_reg_agent() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_DIFFERENT_REG_AGENT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The account owner has at least one active account with the same tax type (OA, SA or SRS) and the Registration Agent entities are different.")); }

        // Actions
	};
}



