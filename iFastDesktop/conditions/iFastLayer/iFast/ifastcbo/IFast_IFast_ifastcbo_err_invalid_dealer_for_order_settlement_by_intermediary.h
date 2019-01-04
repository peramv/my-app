#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_invalid_dealer_for_order_settlement_by_intermediary : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_invalid_dealer_for_order_settlement_by_intermediary() { }
		~CIFast_IFast_ifastcbo_err_invalid_dealer_for_order_settlement_by_intermediary() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_DEALER_FOR_ORDER_SETTLEMENT_BY_INTERMEDIARY")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Dealer cannot settle orders placed by intermediary.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Händler kann Aufträge von Mittlern nicht abrechnen")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El agente no puede liquidar órdenes colocadas por el intermediario")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le courtier ne peut régler des ordres placés par l'intermédiaire.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Handelaar kan geen orders betalen die door tussenpersoon zijn geplaatst")); }

        // Actions
	};
}



