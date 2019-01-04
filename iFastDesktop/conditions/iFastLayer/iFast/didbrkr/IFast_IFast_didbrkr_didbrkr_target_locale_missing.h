#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_didbrkr_didbrkr_target_locale_missing : public CConditionObject
	{
	public:
		CIFast_IFast_didbrkr_didbrkr_target_locale_missing() { }
		~CIFast_IFast_didbrkr_didbrkr_target_locale_missing() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DIDBRKR_TARGET_LOCALE_MISSING")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("didbrkr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Order Source value is invalid for wire order.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Order Source value is invalid for wire order.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Bestellquellen-Wert ist ungültig für telegrafische Bestellung")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El valor de origen de la orden no es válido para la orden de transferencia cablegráfica")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La valeur de la source de l'ordre est invalide pour l'ordre électronique.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Waarde orderbron is ongeldig voor telegrafische order")); }

        // Actions
	};
}



