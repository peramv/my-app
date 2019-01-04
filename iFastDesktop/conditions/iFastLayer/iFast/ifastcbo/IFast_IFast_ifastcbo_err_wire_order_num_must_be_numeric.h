#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_wire_order_num_must_be_numeric : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_wire_order_num_must_be_numeric() { }
		~CIFast_IFast_ifastcbo_err_wire_order_num_must_be_numeric() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_WIRE_ORDER_NUM_MUST_BE_NUMERIC")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Wire Order Number must be numeric.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Wire Order Number must be numeric.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Telegrafische Bestellnummer muss nummerisch sein")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El campo de número de orden de transferencia cablegráfica debe ser numérico")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le numéro d'ordre électronique doit être numérique.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Nummer telegrafische order moet numeriek zijn")); }

        // Actions
	};
}



