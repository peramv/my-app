#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_timestamp : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_timestamp() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_timestamp() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_INVALID_TIMESTAMP")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("No Tax Type record available.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("No Tax Type record available.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Kein Steuerart-Eintrag verfügbar")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No hay registros de tipo tributario disponibles")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Aucun enregistrement de type d'imposition n'est disponible.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er is geen record voor Belastingtype beschikbaar")); }

        // Actions
	};
}



