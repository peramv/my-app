#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_pd_no_blanks_allowed : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_pd_no_blanks_allowed() { }
		~CIFast_IFast_ifastdbrkr_err_pd_no_blanks_allowed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_PD_NO_BLANKS_ALLOWED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Password denied - No blanks allowed.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Mot de passe refuse - Ne doit pas contenir d'espaces")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Kennwort verweigert – Leerstellen sind nicht erlaubt")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Contraseña denegada - No se permiten espacios en blanco")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Mot de passe invalide – aucun espacement n'est accepté.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Wachtwoord geweigerd - Geen spaties toegestaan")); }

        // Actions
	};
}



