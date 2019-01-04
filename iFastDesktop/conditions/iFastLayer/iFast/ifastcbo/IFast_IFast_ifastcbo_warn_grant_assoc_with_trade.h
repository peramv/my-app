#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_grant_assoc_with_trade : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_grant_assoc_with_trade() { }
		~CIFast_IFast_ifastcbo_warn_grant_assoc_with_trade() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_GRANT_ASSOC_WITH_TRADE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("A grant is associated with this trade.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Une subvention est associée à cette transaction.")); }

        // Actions
	};
}



