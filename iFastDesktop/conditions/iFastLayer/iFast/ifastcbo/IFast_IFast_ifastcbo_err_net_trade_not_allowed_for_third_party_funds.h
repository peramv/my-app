#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_net_trade_not_allowed_for_third_party_funds : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_net_trade_not_allowed_for_third_party_funds() { }
		~CIFast_IFast_ifastcbo_err_net_trade_not_allowed_for_third_party_funds() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NET_TRADE_NOT_ALLOWED_FOR_THIRD_PARTY_FUNDS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Net trade is not allowed for third party funds.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Net trade is not allowed for third party funds.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La transaction nette n'est pas autorisée pour les fonds de tiers.")); }

        // Actions
	};
}



