#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_rebalancing_status : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_rebalancing_status() { }
		~CIFast_IFast_ifastcbo_err_rebalancing_status() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_REBALANCING_STATUS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("This status is not applicable.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Ce statut n'est pas applicable.")); }

        // Actions
	};
}



