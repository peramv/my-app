#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_cert_number : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_cert_number() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_cert_number() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_INVALID_CERT_NUMBER")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Net is not allowed for multi-currency trade.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Net is not allowed for multi-currency trade.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Netto ist für Mehrfach-Währungshandel nicht erlaubt.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se permite Neto para una operación en varias divisas")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Net non autorisé pour une transaction multidevises.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Netto is niet toegestaan voor handel in meerdere valuta")); }

        // Actions
	};
}



