#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_first_trade_must_be_transfer : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_first_trade_must_be_transfer() { }
		~CIFast_IFast_ifastcbo_warn_first_trade_must_be_transfer() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_FIRST_TRADE_MUST_BE_TRANSFER")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The first trade into account should be transfer.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La première transaction du compte devrait être un transfert.")); }

        // Actions
	};
}



