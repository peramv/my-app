#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_file_not_closed : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_file_not_closed() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_file_not_closed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_FILE_NOT_CLOSED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Clan Plan maintenance functionality is not available.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Clan Plan maintenance functionality is not available.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Clanplan-Wartungsfunktion ist nicht verfügbar.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La funcionalidad de mantenimiento de Clan Plan no está disponible")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La fonctionnalité de maintenance du régime de clan n'est pas disponible.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Onderhoudsfunctionaliteit Clan Plan is niet beschikbaar")); }

        // Actions
	};
}



