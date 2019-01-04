#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_amount_must_be_zero_for_amounttype_t : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_amount_must_be_zero_for_amounttype_t() { }
		~CIFast_IFast_ifastdbrkr_err_amount_must_be_zero_for_amounttype_t() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_AMOUNT_MUST_BE_ZERO_FOR_AMOUNTTYPE_T")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Amount must be 0 for AmountType T.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Betrag für Betragsart T muss 0 .")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El monto debe ser igual a 0 para el tipo de monto T.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le montant doit être zéro pour le type de montant T.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Bedrag moet 0 zijn voor bedragtype T")); }

        // Actions
	};
}



