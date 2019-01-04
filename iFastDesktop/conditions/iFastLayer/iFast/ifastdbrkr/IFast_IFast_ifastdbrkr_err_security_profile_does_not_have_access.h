#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_security_profile_does_not_have_access : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_security_profile_does_not_have_access() { }
		~CIFast_IFast_ifastdbrkr_err_security_profile_does_not_have_access() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_SECURITY_PROFILE_DOES_NOT_HAVE_ACCESS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Security Profile Id does not have access to this view.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Sicherheitsprofil-ID hat keinen Zugriff auf diese Ansicht")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La identificación de perfil de seguridad no tiene acceso a esta view.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le code de profil de sécurité ne permet pas l'accès à cet affichage.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Beveiligingsprofiel-ID heeft geen toegang tot deze view")); }

        // Actions
	};
}



