#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_invalid_user_id : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_invalid_user_id() { }
		~CIFast_IFast_ifastdbrkr_err_invalid_user_id() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_USER_ID")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid User-Id.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Ungültige Benutzer-ID")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Identificación de usuario no válida")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Code d'utilisateur invalide")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Ongeldig gebruikers-ID")); }

        // Actions
	};
}



