#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dicore_dicore_key_not_found : public CConditionObject
	{
	public:
		CIFast_IFast_dicore_dicore_key_not_found() { }
		~CIFast_IFast_dicore_dicore_key_not_found() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DICORE_KEY_NOT_FOUND")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dicore")); }
		virtual int GetSeverity() const { return 2; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("User status is inactive in Company Database.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("User status is inactive in Company Database.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Benutzerstatus ist inaktiv in der Unternehmer-Datenbank.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El estado del usuario es inactivo en la base de datos de la compañía")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le statut de l'utilisateur est inactif dans la base de données de la Société.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Gebruikersstatus is inactief in de bedrijfsdatabase")); }

        // Actions
	};
}



