#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_net_settlement_not_allowed : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_net_settlement_not_allowed() { }
		~CIFast_IFast_ifastcbo_warn_net_settlement_not_allowed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_Net_SETTLEMENT_NOT_ALLOWED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Net Settlement is not allowed.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le règlement net n’est pas autorisé.")); }

        // Actions
	};
}



