#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_invalid_function_type : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_invalid_function_type() { }
		~CIFast_IFast_dita2kdb_dita2kdb_invalid_function_type() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_INVALID_FUNCTION_TYPE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Password denied - Password has been used recently, choose another.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Mot de passe refuse - Le mot de passe a ete modifie recemment, choisissez-en un autre")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Kennwort verweigert – Kennwort wurde kürzlich geändert, wählen Sie ein anderes")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Contraseña denegada - La contraseña se ha cambiado recientemente, elija otra")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Mot de passe invalide – ce mot de passe a récemment été utilisé, veuillez en choisir un autre.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Wachtwoord geweigerd - Wachtwoord is onlangs gewijzigd, kies een ander")); }

        // Actions
	};
}



