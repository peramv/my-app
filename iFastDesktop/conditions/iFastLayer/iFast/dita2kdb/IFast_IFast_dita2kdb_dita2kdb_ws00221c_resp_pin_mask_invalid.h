#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_pin_mask_invalid : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_pin_mask_invalid() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_pin_mask_invalid() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_PIN_MASK_INVALID")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Shareholder number cannot start with 0.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Le numero d'actionnaire ne peut pas commencer par 0.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Die Aktionärsnummer darf nicht mit 0 beginnen.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El número de accionista no puede comenzar con 0.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le numéro d'actionnaire ne peut commencer par zéro.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Aandeelhoudersnummer kan niet met 0 beginnen")); }

        // Actions
	};
}



