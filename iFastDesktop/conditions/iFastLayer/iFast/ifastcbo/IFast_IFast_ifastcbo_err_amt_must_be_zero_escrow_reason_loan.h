#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_amt_must_be_zero_escrow_reason_loan : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_amt_must_be_zero_escrow_reason_loan() { }
		~CIFast_IFast_ifastcbo_err_amt_must_be_zero_escrow_reason_loan() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_AMT_MUST_BE_ZERO_ESCROW_REASON_LOAN")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Amount must be zero for Escrow/Assigned reason of Loan.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Betrag muss wegen der Treuhand-Anleihen-Begründung null sein")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El monto debe ser cero si el código de motivo de custodia es Préstamo")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le montant doit être de zéro pour la raison de la mise en garantie du prêt.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Bedrag moet nul zijn als redencode pand lening is")); }

        // Actions
	};
}



