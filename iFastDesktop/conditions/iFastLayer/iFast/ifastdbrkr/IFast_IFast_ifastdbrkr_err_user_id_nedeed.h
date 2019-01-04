#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_user_id_nedeed : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_user_id_nedeed() { }
		~CIFast_IFast_ifastdbrkr_err_user_id_nedeed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_USER_ID_NEDEED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("User-ID is needed to confirm your identity.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Benutzer-ID wird benötigt, um Ihre Identität zu bestätigen")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Se necesita la identificación del usuario para confirmar su identidad")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le code d'utilisateur est requis afin de confirmer votre identité.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Gebruikers-ID is nodig om uw identiteit te bevestigen")); }

        // Actions
	};
}



