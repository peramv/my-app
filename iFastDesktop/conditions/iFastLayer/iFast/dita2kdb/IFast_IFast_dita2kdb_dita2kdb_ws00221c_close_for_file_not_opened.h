#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_close_for_file_not_opened : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_close_for_file_not_opened() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_close_for_file_not_opened() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_CLOSE_FOR_FILE_NOT_OPENED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("No Branch is found.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Aucun supérieur hiérarchique exist avec les co-ordonnées que vous avez spécifié.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Keine Filiale gefunden")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se ha encontrado una sucursal")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Aucune unité de service n'a été trouvée.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er is geen filiaal gevonden")); }

        // Actions
	};
}



