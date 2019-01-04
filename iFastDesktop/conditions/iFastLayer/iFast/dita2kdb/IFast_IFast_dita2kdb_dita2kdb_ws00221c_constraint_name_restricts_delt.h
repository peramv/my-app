#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_constraint_name_restricts_delt : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_constraint_name_restricts_delt() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_constraint_name_restricts_delt() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_CONSTRAINT_NAME_RESTRICTS_DELT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("No mailing information is available for the shareholder.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("No mailing information is available for the shareholder.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Keine Mailing-Informationen für den Aktionär verfügbar.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No hay información de correspondencia  disponible para el accionista")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Aucune information postale n'est disponible pour l'actionnaire.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er zijn geen mailinggegevens beschikbaar voor de aandeelhouder")); }

        // Actions
	};
}



