#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_invalid_purch_cancel : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_invalid_purch_cancel() { }
		~CIFast_IFast_dita2kdb_dita2kdb_invalid_purch_cancel() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_INVALID_PURCH_CANCEL")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Password denied - Only one repetition of a character allowed.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Mot de passe refuse - Une seule repetition de caractere autorisée")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Kennwort verweigert – Nur eine Wiederholung von Schriftzeichen erlaubt")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Contraseña denegada - Sólo se permite repetir 1 carácter")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Mot de passe invalide – un caractère ne peut être répété qu'une seule fois.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Wachtwoord geweigerd - Slechts één herhaling van tekens toegestaan")); }

        // Actions
	};
}



