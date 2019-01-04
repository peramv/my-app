#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_file_access_error : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_file_access_error() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_file_access_error() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_FILE_ACCESS_ERROR")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Automatic Transfer with the same fund/class and effective already exists.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Automatic Transfer with the same fund/class and effective already exists.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Automatischer Transfer mit der/s gleichen Fonds/Klasse und Effektivdatum existiert bereits.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La transferencia automática con el mismo fondo/clase y fecha de entrada en vigencia ya existe.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le transfert automatique avec le même fonds/la même classe et l'en-vigueur existent déjà.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Automatische overdracht met hetzelfde fonds of dezelfde categorie en ingangsdatum bestaat al")); }

        // Actions
	};
}



