#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_exch_funds_equal : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_exch_funds_equal() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_exch_funds_equal() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_EXCH_FUNDS_EQUAL")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("No pension information available.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("No pension information available.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Keine Renteninformationen verfügbar.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No hay información de jubilación disponible")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Aucune information sur le fonds de pension n'est disponible.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er zijn geen pensioengegevens beschikbaar")); }

        // Actions
	};
}



