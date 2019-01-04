#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_ad_unknown_user : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_ad_unknown_user() { }
		~CIFast_IFast_ifastdbrkr_err_ad_unknown_user() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_AD_UNKNOWN_USER")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Access denied - Unknown user.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Acces refuse - Utilisateur inconnu")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Zugriff verweigert – Unbekannter Benutzer")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Acceso denegado - Usuario desconocido")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Accès refusé – utilisateur inconnu")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Toegang geweigerd - Onbekende gebruiker")); }

        // Actions
	};
}



