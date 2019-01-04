#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_source_system_id : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_source_system_id() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_source_system_id() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_INVALID_SOURCE_SYSTEM_ID")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("No active batch available.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Aucun lot actif n'est disponible.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Kein aktiver Batch verfügbar.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No hay un lote activo disponible")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Aucun lot actif n'est disponible.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er is geen actieve batch beschikbaar")); }

        // Actions
	};
}



