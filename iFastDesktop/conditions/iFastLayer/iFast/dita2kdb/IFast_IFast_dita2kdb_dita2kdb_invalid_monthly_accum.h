#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_invalid_monthly_accum : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_invalid_monthly_accum() { }
		~CIFast_IFast_dita2kdb_dita2kdb_invalid_monthly_accum() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_INVALID_MONTHLY_ACCUM")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Password denied - Unknown access profile.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Mot de passe refuse - Profil d'acces inconnu")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Kennwort verweigert – Unbekanntes Zugriffsprofil")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Contraseña denegada - Perfil de acceso desconocido")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Mot de passe invalide – profil d'accès inconnu")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Wachtwoord geweigerd - Onbekend toegangsprofiel")); }

        // Actions
	};
}



