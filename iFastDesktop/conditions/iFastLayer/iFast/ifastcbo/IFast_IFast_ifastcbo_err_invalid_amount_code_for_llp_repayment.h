#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_invalid_amount_code_for_llp_repayment : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_invalid_amount_code_for_llp_repayment() { }
		~CIFast_IFast_ifastcbo_err_invalid_amount_code_for_llp_repayment() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_AMOUNT_CODE_FOR_LLP_REPAYMENT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid amount code for LLP repayment.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Ungültiger Betrags-Code für LLP-Rückzahlung")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Código de monto no válido para reembolso LLP")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Code de montant invalide pour le remboursement REEP")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Ongeldige bedragcode voor terugbetaling LPP")); }

        // Actions
	};
}



