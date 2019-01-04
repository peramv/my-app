#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_b08_record_not_found : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_b08_record_not_found() { }
		~CIFast_IFast_dita2kdb_dita2kdb_b08_record_not_found() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_B08_RECORD_NOT_FOUND")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Password denied - Need 2 or more non-alpha characters.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Mot de passe refuse - 2 caracteres non alphabetiques minimum requis")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Kennwort verweigert – 2 oder mehr Alphaschriftzeichen notwendig")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Contraseña denegada - Se necesitan 2 o más caracteres no alfabéticos")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Mot de passe invalide – vous devez utiliser 2 caractères non alphabétiques ou plus.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Wachtwoord geweigerd - Twee of meer niet-alfabetische tekens nodig")); }

        // Actions
	};
}



