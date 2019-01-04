#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_invalid_start_year : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_invalid_start_year() { }
		~CIFast_IFast_dita2kdb_dita2kdb_invalid_start_year() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_INVALID_START_YEAR")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Access denied - Unknown user.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Acces refuse - Utilisateur inconnu")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Zugriff verweigert – Unbekannter Benutzer")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Acceso denegado - Usuario desconocido")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Accès refusé – utilisateur inconnu")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Toegang geweigerd - Onbekende gebruiker")); }

        // Actions
	};
}



