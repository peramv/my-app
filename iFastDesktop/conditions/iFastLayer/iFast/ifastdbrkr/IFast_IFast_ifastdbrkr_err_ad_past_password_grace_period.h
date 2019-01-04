#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_ad_past_password_grace_period : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_ad_past_password_grace_period() { }
		~CIFast_IFast_ifastdbrkr_err_ad_past_password_grace_period() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_AD_PAST_PASSWORD_GRACE_PERIOD")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Access denied - Past password grace period.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Acces refuse - Delai de grace de mot de passe revolu")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Zugriff verweigert – Nach Kennwort-Frist-Periode")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Acceso denegado - Pasó el período de gracia de la contraseña")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Accès refusé – délai de grâce du mot de passe dépassé")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Toegang geweigerd - Na vervalperiode wachtwoord")); }

        // Actions
	};
}



