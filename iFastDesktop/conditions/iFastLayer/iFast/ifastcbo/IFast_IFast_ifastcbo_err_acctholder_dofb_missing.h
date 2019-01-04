#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_acctholder_dofb_missing : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_acctholder_dofb_missing() { }
		~CIFast_IFast_ifastcbo_err_acctholder_dofb_missing() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ACCTHOLDER_DOFB_MISSING")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Account holder's birth date is missing, unable to calculate minimum payment.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Geburtsdatum des Kontoinhabers fehlt, Minimum-Zahlung kann nicht berechnet werden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Falta la fecha de nacimiento del titular de la cuenta, imposible calcular el pago mínimo.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La date de naissance du titulaire du compte est manquante, impossible de calculer le paiement minimal.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Geboortedatum accounthouder ontbreekt, minimumbetaling kan niet worden berekend")); }

        // Actions
	};
}



