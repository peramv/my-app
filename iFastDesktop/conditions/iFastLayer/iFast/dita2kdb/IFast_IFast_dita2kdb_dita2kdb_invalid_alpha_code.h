#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_invalid_alpha_code : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_invalid_alpha_code() { }
		~CIFast_IFast_dita2kdb_dita2kdb_invalid_alpha_code() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_INVALID_ALPHA_CODE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("An invalid wide-character code has been detected.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("An invalid wide-character code has been detected.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Ein ungültiger Code mit breiten Schriftzeichen wurde festgestellt.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Se ha detectado un código de caracteres anchos no válido.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Un code de caractère large invalide a été détecté.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er is een ongeldige code voor brede tekens aangetroffen")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Check system")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Verifiez le systeme.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Überprüfen Sie das System")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Check system")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Vérifiez le système.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Controleer het systeem")); }
	};
}



