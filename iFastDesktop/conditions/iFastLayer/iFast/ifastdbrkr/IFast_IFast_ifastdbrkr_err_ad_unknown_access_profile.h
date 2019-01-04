#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_ad_unknown_access_profile : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_ad_unknown_access_profile() { }
		~CIFast_IFast_ifastdbrkr_err_ad_unknown_access_profile() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_AD_UNKNOWN_ACCESS_PROFILE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Access denied - Unknown access profile.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Acces refuse - Profil d'acces inconnu")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Zugriff verweigert – Unbekanntes Zugriffsprofil")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Acceso denegado - Perfil de acceso desconocido")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Accès refusé – profil d'accès inconnu")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Toegang geweigerd - Onbekend toegangsprofiel")); }

        // Actions
	};
}



