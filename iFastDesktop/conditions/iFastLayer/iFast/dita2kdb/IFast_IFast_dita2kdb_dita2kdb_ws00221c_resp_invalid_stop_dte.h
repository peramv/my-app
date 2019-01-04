#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_stop_dte : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_stop_dte() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_stop_dte() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_INVALID_STOP_DTE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Multiple address matches were found.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Multiple address matches were found.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Mehrere Adress-Entsprechungen wurden gefunden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Se encontraron varias direcciones coincidentes")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Plusieurs correspondances d'adresse trouvées")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er zijn meerdere overeenstemmende adressen gevonden")); }

        // Actions
	};
}



