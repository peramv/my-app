#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_net_redemption_over_minimum : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_net_redemption_over_minimum() { }
		~CIFast_IFast_ifastcbo_err_net_redemption_over_minimum() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NET_REDEMPTION_OVER_MINIMUM")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The requested amount has exceeded the minimum.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le montant requis excède le minimum.")); }

        // Actions
	};
}



