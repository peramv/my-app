#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_user_does_not_exists : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_user_does_not_exists() { }
		~CIFast_IFast_ifastdbrkr_err_user_does_not_exists() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_USER_DOES_NOT_EXISTS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("User does not exist in the system.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Benutzer im System nicht vorhanden")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El usuario no existe en el sistema")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Utilisateur inexistant dans le système")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Gebruiker bestaat niet in het systeem")); }

        // Actions
	};
}



