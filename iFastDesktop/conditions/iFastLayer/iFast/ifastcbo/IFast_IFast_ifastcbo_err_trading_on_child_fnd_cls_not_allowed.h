#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_trading_on_child_fnd_cls_not_allowed : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_trading_on_child_fnd_cls_not_allowed() { }
		~CIFast_IFast_ifastcbo_err_trading_on_child_fnd_cls_not_allowed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_TRADING_ON_CHILD_FND_CLS_NOT_ALLOWED_ACCT_NOT_LINKED_TO_ANY_AMS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Trading on child fund class not allowed account not linked to any AMS.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Trading on child fund class not allowed account not linked to any AMS.")); }

        // Actions
	};
}