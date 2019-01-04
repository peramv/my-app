#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_amount_must_be_zero_when_closing_account : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_amount_must_be_zero_when_closing_account() { }
		~CIFast_IFast_ifastcbo_err_amount_must_be_zero_when_closing_account() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_AMOUNT_MUST_BE_ZERO_WHEN_CLOSING_ACCOUNT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Amount must be zero when closing account.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Der Betrag muss null sein, wenn das Konto abgeschlossen wird")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El monto debe ser igual a cero al cerrar la cuenta")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le montant doit être de zéro lors de la fermeture du compte.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Bedrag moet nul zijn als het account wordt gesloten")); }

        // Actions
	};
}



