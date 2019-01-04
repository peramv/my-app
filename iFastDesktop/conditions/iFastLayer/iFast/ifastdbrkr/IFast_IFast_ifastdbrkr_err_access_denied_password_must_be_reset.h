#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_access_denied_password_must_be_reset : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_access_denied_password_must_be_reset() { }
		~CIFast_IFast_ifastdbrkr_err_access_denied_password_must_be_reset() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ACCESS_DENIED_PASSWORD_MUST_BE_RESET")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Access denied. Password must be reset.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Acces refuse. Le mot de passe doit être reinitialise.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Zugriff verweigert. Kennwort muss neu erstellt werden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Acceso denegado. Debe reconfigurarse la contraseña.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Accès refusé. Le mot de passe doit être réinitialisé.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Toegang geweigerd. Wachtwoord moet opnieuw worden ingesteld")); }

        // Actions
	};
}



