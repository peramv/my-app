#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_max_io_limit : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_max_io_limit() { }
		~CIFast_IFast_dita2kdb_dita2kdb_max_io_limit() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_MAX_IO_LIMIT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid characters.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Caracteres invalides. Veuillez ressaisir des caracteres.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Ungültige Zeichenfolge. Bitte geben Sie neu ein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Caracteres no válidos. Por favor vuelva a introducir los datos.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Caratères invalides")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Ongeldige tekens. Vul opnieuw in")); }

        // Actions
	};
}



