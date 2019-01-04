#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_invalid_fid_account : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_invalid_fid_account() { }
		~CIFast_IFast_dita2kdb_dita2kdb_invalid_fid_account() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_INVALID_FID_ACCOUNT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Password denied - three of the same characters not allowed.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Mot de passe refuse - Saisie de trois caracteres identiques non autorisée")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Kennwort verweigert – drei gleiche Schriftzeichen sind nicht erlaubt")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Contraseña denegada - No se permiten 3 caracteres iguales")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Mot de passe invalide – vous ne pouvez utiliser trois fois le même caractère.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Wachtwoord geweigerd - Drie dezelfde tekens zijn niet toegestaan")); }

        // Actions
	};
}



