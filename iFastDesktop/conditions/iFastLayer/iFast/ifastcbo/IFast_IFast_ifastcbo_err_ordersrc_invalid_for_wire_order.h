#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_ordersrc_invalid_for_wire_order : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_ordersrc_invalid_for_wire_order() { }
		~CIFast_IFast_ifastcbo_err_ordersrc_invalid_for_wire_order() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ORDERSRC_INVALID_FOR_WIRE_ORDER")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Order Source 'F' is invaild for wire order trade.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Bestellquelle \"F\" ist ungültig für telegrafischen Bestellhandel")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El origen de orden \"F\" no es válido para la orden de transferencia cablegráfica")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La source d'ordre F est invalide pour la transaction d'ordre électronique.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Orderbron 'F' is ongeldig voor handel per telegrafische order")); }

        // Actions
	};
}



