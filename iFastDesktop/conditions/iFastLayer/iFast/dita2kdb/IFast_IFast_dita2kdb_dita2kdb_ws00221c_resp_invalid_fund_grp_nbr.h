#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_fund_grp_nbr : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_fund_grp_nbr() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_fund_grp_nbr() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_INVALID_FUND_GRP_NBR")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Access denied - database not connected.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Access denied - database not connected.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Zugriff verweigert – Datenbank nicht verbunden")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Acceso denegado - La base de datos no está conectada.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Accès refusé – la base de données n'est pas connectée.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Toegang geweigerd - database is niet aangesloten")); }

        // Actions
	};
}



