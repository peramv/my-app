#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_state_upd_code : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_state_upd_code() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_state_upd_code() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_INVALID_STATE_UPD_CODE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Cannot create batch.  No unique name found.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Cannot create batch.  No unique name found.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Batch kann nicht erstellt werden, kein eindeutiger Name gefunden")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se puede crear el lote, no se encontró un nombre único")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Impossible de créer le lot. Aucun nom unique trouvé.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Batch kon niet worden gemaakt, er is geen unieke naam gevonden")); }

        // Actions
	};
}



