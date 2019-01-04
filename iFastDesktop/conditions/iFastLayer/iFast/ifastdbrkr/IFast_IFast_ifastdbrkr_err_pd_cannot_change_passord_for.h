#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_pd_cannot_change_passord_for : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_pd_cannot_change_passord_for() { }
		~CIFast_IFast_ifastdbrkr_err_pd_cannot_change_passord_for() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_PD_CANNOT_CHANGE_PASSORD_FOR")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Password denied - Can not change password for %threshold% more days.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Mot de passe refuse - Impossible de modifier le mot de passe pour %threshold% jours supplementaires")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Kennwort verweigert – Kennwort kann nicht für %threshold% weitere geändert werden")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Contraseña denegada - No se puede cambiar la contraseña por %threshold% días más")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Mot de passe invalide – impossible de changer le mot de passe avant %threshold% jours de plus.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Wachtwoord geweigerd - Wachtwoord kan pas worden gewijzigd over %threshold% dagen")); }

        // Actions
	};
}



