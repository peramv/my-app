#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_broker_min_balance : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_broker_min_balance() { }
		~CIFast_IFast_ifastcbo_warn_broker_min_balance() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_BROKER_MIN_BALANCE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Broker: Less then minimum Fund/Class balance.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Courtier : inférieur au solde minimal du fonds/de la classe")); }

        // Actions
	};
}



