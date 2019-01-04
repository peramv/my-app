#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_wire_num_not_numeric : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_wire_num_not_numeric() { }
		~CIFast_IFast_ifastcbo_err_wire_num_not_numeric() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_WIRE_NUM_NOT_NUMERIC")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Wire Order Number should be numeric.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Telegrafische Bestellnummer sollte nummerisch sein")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El campo de número de orden de transferencia cablegráfica debe ser numérico")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le numéro d'ordre électronique devrait être numérique.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Nummer telegrafische order moet numeriek zijn")); }

        // Actions
	};
}



