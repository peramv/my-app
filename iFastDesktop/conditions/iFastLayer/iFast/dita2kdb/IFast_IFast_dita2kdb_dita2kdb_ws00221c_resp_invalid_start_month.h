#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_start_month : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_start_month() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_start_month() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_INVALID_START_MONTH")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid amount type for Purchase.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Type de montant invalide pour souscription")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Ungültige Betragsart für Kauf.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Tipo de monto no válido para compra")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Type de montant invalide pour l'achat")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Ongeldig bedragtype voor aankoop")); }

        // Actions
	};
}



