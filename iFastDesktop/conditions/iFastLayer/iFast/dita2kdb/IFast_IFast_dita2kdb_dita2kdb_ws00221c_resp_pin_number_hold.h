#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_pin_number_hold : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_pin_number_hold() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_pin_number_hold() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_PIN_NUMBER_HOLD")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("No processed RESP trades.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("No processed RESP trades.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Keine verarbeiteten RESP-Handel.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No hay operaciones RESP procesadas.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Aucune transaction REEE traitée")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Geen verwerkte RESP-transacties")); }

        // Actions
	};
}



