#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_invalid_rein_dollar : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_invalid_rein_dollar() { }
		~CIFast_IFast_dita2kdb_dita2kdb_invalid_rein_dollar() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_INVALID_REIN_DOLLAR")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Could not create the shareholder remarks record.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Impossible de creer l'enregistrement des remarques relatives a l'actionnaire")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Der Eintrag mit den Kommentaren des Aktionärs konnte nicht erstellt werden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se pudo crear el registro de comentarios del accionista")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Impossible de créer l'enregistrement des remarques de l'actionnaire.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Het opmerkingenrecord voor de aandeelhouder kon niet worden gemaakt")); }

        // Actions
	};
}



