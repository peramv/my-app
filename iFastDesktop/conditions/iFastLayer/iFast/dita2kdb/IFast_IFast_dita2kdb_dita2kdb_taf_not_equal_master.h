#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_taf_not_equal_master : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_taf_not_equal_master() { }
		~CIFast_IFast_dita2kdb_dita2kdb_taf_not_equal_master() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_TAF_NOT_EQUAL_MASTER")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Password denied - Unknown user.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Mot de passe refuse - Utilisateur inconnu")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Kennwort verweigert – Unbekannter Benutzer")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Contraseña denegada - Usuario desconocido")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Mot de passe invalide – utilisateur inconnu")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Wachtwoord geweigerd - Onbekende gebruiker")); }

        // Actions
	};
}



