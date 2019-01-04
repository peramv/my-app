#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_account_number_mustbe_blank : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_account_number_mustbe_blank() { }
		~CIFast_IFast_ifastdbrkr_err_account_number_mustbe_blank() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ACCOUNT_NUMBER_MUSTBE_BLANK")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Account Number must be blank for TransPending S, D or L.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Kontonummer für TransPending S, D oder L muss leer sein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El número de cuenta debe estar en blanco para transacción pendiente S, D o L.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le champ du numéro de compte doit être vide pour les transaction en suspens S, D ou L.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Accountnummer moet leeg zijn voor in behandeling zijnde transacties S, D of L")); }

        // Actions
	};
}



