#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_specifie_fund_when_amount_is_zero : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_specifie_fund_when_amount_is_zero() { }
		~CIFast_IFast_ifastcbo_err_specifie_fund_when_amount_is_zero() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_SPECIFIE_FUND_WHEN_AMOUNT_IS_ZERO")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("You must specify a fund when amount is zero and you are not closing an account.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Sie müssen einen Fonds spezifizieren, wenn der Betrag null ist und Sie das Konto nicht schließen")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Debe especificar un fondo cuando el monto es cero y no está cerrando una cuenta")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Vous devez spécifier un fonds lorsque le montant est de zéro et que vous n'êtes pas en train de fermer un compte.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("U moet een fonds opgeven als het bedrag nul is en u het account niet sluit")); }

        // Actions
	};
}



