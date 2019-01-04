#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_invalid_broker_for_money_market_wire_orders : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_invalid_broker_for_money_market_wire_orders() { }
		~CIFast_IFast_ifastcbo_err_invalid_broker_for_money_market_wire_orders() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_BROKER_FOR_MONEY_MARKET_WIRE_ORDERS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Broker is not permitted to place money market wire orders.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Broker is not permitted to place money market wire orders.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le courtier n'est pas autorisé à lancer des ordres électroniques de valeur du marché.")); }

        // Actions
	};
}



