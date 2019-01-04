#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_acct_num_blank_for_transpending : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_acct_num_blank_for_transpending() { }
		~CIFast_IFast_ifastdbrkr_err_acct_num_blank_for_transpending() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ACCT_NUM_BLANK_FOR_TRANSPENDING")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Account Number must be blank for TransPending S, D or L.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Kontonummer für schwebende Transaktion S, D oder L muss leer sein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El número de cuenta debe estar en blanco para transacciones pendientes S, D o L.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le champ Numéro de compte doit être vide pour les transactions en suspens S, D ou L.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Accountnummer moet leeg zijn voor in behandeling zijnde transacties S, D of L")); }

        // Actions
	};
}



