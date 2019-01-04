#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_pd_only_seven_chars_in_a_row : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_pd_only_seven_chars_in_a_row() { }
		~CIFast_IFast_ifastdbrkr_err_pd_only_seven_chars_in_a_row() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_PD_ONLY_SEVEN_CHARS_IN_A_ROW")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Password denied - Only seven characters in a row.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Mot de passe refuse - Sept caracteres uniquement dans une ligne")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Kennwort verweigert – Nur sieben Schriftzeichen in einer Reihe")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Contraseña denegada - Sólo se permiten 7 caracteres por fila")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Mot de passe invalide – seulement sept caractères par rangée")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Wachtwoord geweigerd - Slechts zeven tekens op rij")); }

        // Actions
	};
}



