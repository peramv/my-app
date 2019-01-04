#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_user_cannot_access_account : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_user_cannot_access_account() { }
		~CIFast_IFast_ifastdbrkr_err_user_cannot_access_account() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_USER_CANNOT_ACCESS_ACCOUNT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("User cannot access this account.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Benutzer kann nicht auf dieses Konto zugreifen")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El usuario no puede acceder a esta cuenta")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'utilisateur ne peut accéder à ce compte.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Gebruiker kan dit account niet openen")); }

        // Actions
	};
}



