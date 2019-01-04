#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_access_denied : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_access_denied() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_access_denied() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_ACCESS_DENIED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Corresponding assigned units information not found.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Corresponding assigned units information not found.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Entsprechende zugewiesene Anteil-Informationen nicht gefunden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se encontró información de unidades asignadas correspondiente")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'information sur les unités mises en garantie correspondantes est introuvable.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Bijbehorende gegevens toegewezen eenheden zijn niet gevonden")); }

        // Actions
	};
}



