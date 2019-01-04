#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_exch_red_canc : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_exch_red_canc() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_exch_red_canc() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_INVALID_EXCH_RED_CANC")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Contract Term's value is outside of range.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Contract Term's value is outside of range.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Der Wert der Vertragsbedingungen liegt außerhalb des Bereichs.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El valor de la duración del contrato se encuentra fuera de rango.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La valeur de l'échéance du contrat est hors plage.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Waarde overeenkomstduur ligt buiten het bereik")); }

        // Actions
	};
}



