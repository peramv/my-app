#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_fee_set_up_is_not_allowed : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_fee_set_up_is_not_allowed() { }
		~CIFast_IFast_ifastcbo_err_fee_set_up_is_not_allowed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FEE_SET_UP_IS_NOT_ALLOWED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Fund level fee is not available or does not allow user to override.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Provision auf Fonds-Level ist nicht verfügbar oder dem Benutzer ist es nicht erlaubt, dies außer Kraft zu setzen.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La comisión a nivel del fondo no está disponible o no permite al usuario reemplazarla.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les frais au niveau du compte ne sont pas disponibles ou ne permettent pas à l'utilisateur d'effectuer une modification.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Kosten op fondsniveau zijn niet beschikbaar of de gebruiker kan ze niet vervangen")); }

        // Actions
	};
}



