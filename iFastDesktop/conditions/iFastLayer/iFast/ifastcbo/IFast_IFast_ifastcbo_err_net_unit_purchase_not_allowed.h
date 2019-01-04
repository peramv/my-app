#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_net_unit_purchase_not_allowed : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_net_unit_purchase_not_allowed() { }
		~CIFast_IFast_ifastcbo_err_net_unit_purchase_not_allowed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NET_UNIT_PURCHASE_NOT_ALLOWED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Net unit Purchases are not allowed.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Net unit Purchases are not allowed.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Net unit Purchases are not allowed.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les achats nets en unités ne sont pas autorisés.")); }

        // Actions
	};
}



