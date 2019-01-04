#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_invalid_redmpt_cancel : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_invalid_redmpt_cancel() { }
		~CIFast_IFast_dita2kdb_dita2kdb_invalid_redmpt_cancel() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_INVALID_REDMPT_CANCEL")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Password denied - Only seven characters in a row.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Mot de passe refuse - Sept caracteres uniquement dans une ligne")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Kennwort verweigert – Nur sieben Schriftzeichen in einer Reihe")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Contraseña denegada - Sólo se permiten 7 caracteres por fila")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Mot de passe invalide – seulement sept caractères par rangée")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Wachtwoord geweigerd - Slechts zeven tekens op rij")); }

        // Actions
	};
}



