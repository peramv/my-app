#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_a52_info_unavail : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_a52_info_unavail() { }
		~CIFast_IFast_dita2kdb_dita2kdb_a52_info_unavail() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_A52_INFO_UNAVAIL")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Password denied - Change Password not allowed for user.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Mot de passe refuse - Option Modifier mot de passe interdite a l'utilisateur")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Kennwort verweigert – Kennwortänderung für Benutzer nicht erlaubt")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Contraseña denegada - No se permite cambiar la contraseña al usuario")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Mot de passe invalide – l'utilisateur n'est pas autorisé à changer le mot de passe.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Wachtwoord geweigerd - Wachtwoord wijzigen niet toegestaan voor gebruiker")); }

        // Actions
	};
}



