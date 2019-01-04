#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_city_entered : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_city_entered() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_city_entered() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_INVALID_CITY_ENTERED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Cannot create batch, no user id.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Cannot create batch, no user id.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Batch kann nicht erstellt werden, keine Benutzer-ID")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se puede crear el lote, no hay identificación de usuario")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Impossible de créer le lot, aucun code d'utilisateur.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Batch kon niet worden gemaakt, geen gebruikers-ID")); }

        // Actions
	};
}



