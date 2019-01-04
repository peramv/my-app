#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_file_not_on_reel : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_file_not_on_reel() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_file_not_on_reel() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_FILE_NOT_ON_REEL")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Last name is required.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Un nom patronymique est requis.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Nachname ist erforderlich.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El apellido es obligatorio.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le nom de famille est requis.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Achternaam is vereist")); }

        // Actions
	};
}



