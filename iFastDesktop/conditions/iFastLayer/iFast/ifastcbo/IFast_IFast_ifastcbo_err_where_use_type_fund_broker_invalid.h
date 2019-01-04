#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_where_use_type_fund_broker_invalid : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_where_use_type_fund_broker_invalid() { }
		~CIFast_IFast_ifastcbo_err_where_use_type_fund_broker_invalid() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_WHERE_USE_TYPE_FUND_BROKER_INVALID")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("You can only attach a Fund Broker using the Fund Broker screen.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Vous ne pouvez saisir un courtier en fonds qu'en utilisant l'écran du courtier en fonds.")); }

        // Actions
	};
}



