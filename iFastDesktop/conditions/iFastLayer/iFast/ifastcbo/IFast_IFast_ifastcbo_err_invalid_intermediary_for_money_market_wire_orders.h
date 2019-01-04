#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_invalid_intermediary_for_money_market_wire_orders : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_invalid_intermediary_for_money_market_wire_orders() { }
		~CIFast_IFast_ifastcbo_err_invalid_intermediary_for_money_market_wire_orders() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_INTERMEDIARY_FOR_MONEY_MARKET_WIRE_ORDERS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Intermediary not permitted to enter money market wire orders.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Mittler kann keine telegrafischen Bestellungen für den Geldmarkt eingeben")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se permite al intermediario introducir órdenes de transferencias cablegráficas del mercado monetario")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'intermédiaire n'est pas autorisé à entrer des ordres électroniques du marché monétaire.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Tussenpersoon mag geen telegrafische orders voor de geldmarkt invoeren")); }

        // Actions
	};
}



