#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_ad_user_account_not_active : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_ad_user_account_not_active() { }
		~CIFast_IFast_ifastdbrkr_err_ad_user_account_not_active() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_AD_USER_ACCOUNT_NOT_ACTIVE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Access denied - User account not active.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Acces refuse - Compte d'utilisateur desactive")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Zugriff verweigert – Benutzerkonto nicht aktiv")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Acceso denegado - La cuenta del usuario no está activa")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Accès refusé – le compte de l'utilisateur est inactif.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Toegang geweigerd - Gebruikersaccount is niet actief")); }

        // Actions
	};
}



