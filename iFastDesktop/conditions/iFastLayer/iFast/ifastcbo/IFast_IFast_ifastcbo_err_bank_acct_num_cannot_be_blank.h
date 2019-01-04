#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_bank_acct_num_cannot_be_blank : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_bank_acct_num_cannot_be_blank() { }
		~CIFast_IFast_ifastcbo_err_bank_acct_num_cannot_be_blank() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_BANK_ACCT_NUM_CANNOT_BE_BLANK")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Bank account number cannot be blank.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Bankkontonummer darf nicht leer sein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El número de cuenta bancaria no puede estar en blanco.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le champ Numéro de compte bancaire doit être rempli.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Nummer bankrekening kan niet leeg zijn")); }

        // Actions
	};
}



