#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_amount_must_be_zero_if_escrow_reason_code_is_bankruptcy : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_amount_must_be_zero_if_escrow_reason_code_is_bankruptcy() { }
		~CIFast_IFast_ifastcbo_err_amount_must_be_zero_if_escrow_reason_code_is_bankruptcy() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_AMOUNT_MUST_BE_ZERO_IF_ESCROW_REASON_CODE_IS_BANKRUPTCY")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Amount must be zero if escrow/Assigned reason code is Bankruptcy.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Betrag muss null sein, wenn Escrow-Begründungs-Code Konkurs ist.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El monto debe ser cero si el código de motivo de custodia es quiebra")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le montant doit être de zéro si le code de raison de la mise en garantie est la faillite.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Bedrag moet nul zijn als redencode pand faillissement is")); }

        // Actions
	};
}



