#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_function_disabled : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_function_disabled() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_function_disabled() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_FUNCTION_DISABLED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("No valid shareholder or account number has been provided.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Aucun numero d'actionnaire ou de compte valide n'a ete saisi.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Kein gültiger Aktionär oder Kontonummer verfügbar.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se ha proporcionado ningún número de accionista o cuenta válidos")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Aucun actionnaire ou numéro de compte valide n'a été fourni.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er is geen geldig nummer voor de aandeelhouder of het account opgegeven")); }

        // Actions
	};
}



