#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_mgmt_co_not_found : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_mgmt_co_not_found() { }
		~CIFast_IFast_dita2kdb_dita2kdb_mgmt_co_not_found() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_MGMT_CO_NOT_FOUND")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Access denied - Shareholder does not exist.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Acces refuse - Actionnaire n'existe pas")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Zugriff verweigert – Aktionär existiert nicht")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Acceso denegado - El accionista no existe")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Accès refusé – actionnaire inexistant")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Toegang geweigerd - Aandeelhouder bestaat niet")); }

        // Actions
	};
}



