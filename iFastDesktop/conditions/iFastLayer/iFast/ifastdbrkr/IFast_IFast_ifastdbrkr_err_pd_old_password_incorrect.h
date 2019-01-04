#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_pd_old_password_incorrect : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_pd_old_password_incorrect() { }
		~CIFast_IFast_ifastdbrkr_err_pd_old_password_incorrect() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_PD_OLD_PASSWORD_INCORRECT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Password denied - Old password incorrect.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Mot de passe refuse - Ancien mot de passe incorrect")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Kennwort verweigert – Altes Kennwort nicht korrekt")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Contraseña denegada - La contraseña anterior es incorrecta")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Mot de passe invalide – ancien mot de passe incorrect")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Wachtwoord geweigerd - Oude wachtwoord is onjuist")); }

        // Actions
	};
}



