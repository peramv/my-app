#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_pin_number_inactive : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_pin_number_inactive() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_pin_number_inactive() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_PIN_NUMBER_INACTIVE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Bank account number must be numeric.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Bank account number must be numeric.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Bankkontonummer muss nummerisch sein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El número de cuenta bancaria debe ser numérico")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le numéro de compte bancaire doit être numérique.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Nummer bankrekening moet numeriek zijn")); }

        // Actions
	};
}



