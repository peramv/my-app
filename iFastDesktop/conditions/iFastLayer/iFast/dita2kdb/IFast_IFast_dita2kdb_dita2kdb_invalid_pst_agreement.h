#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_invalid_pst_agreement : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_invalid_pst_agreement() { }
		~CIFast_IFast_dita2kdb_dita2kdb_invalid_pst_agreement() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_INVALID_PST_AGREEMENT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Password denied - Old password incorrect.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Mot de passe refuse - Ancien mot de passe incorrect")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Kennwort verweigert – Altes Kennwort nicht korrekt")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Contraseña denegada - La contraseña anterior es incorrecta")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Mot de passe invalide – ancien mot de passe incorrect")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Wachtwoord geweigerd - Oude wachtwoord is onjuist")); }

        // Actions
	};
}



