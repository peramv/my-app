#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_dfhresp_qiderr : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_dfhresp_qiderr() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_dfhresp_qiderr() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_DFHRESP_QIDERR")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Database unavailable.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Database unavailable.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Datenbank nicht verfügbar.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La base de datos no está disponible.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La base de données n'est pas disponible.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Database is onbeschikbaar")); }

        // Actions
	};
}



