#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_amount_cannot_be_greater_amount_type_p : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_amount_cannot_be_greater_amount_type_p() { }
		~CIFast_IFast_ifastdbrkr_err_amount_cannot_be_greater_amount_type_p() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_AMOUNT_CANNOT_BE_GREATER_AMOUNT_TYPE_P")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Amount cannot be greater than 100 for AmountType P.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Betrag kann für Betragsart P nicht größer als 100 sein")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El monto no puede ser mayor que 100 para el tipo de monto P")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le montant ne peut être supérieur à 100 pour le type de montant P.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Bedrag kan niet hoger zijn dan 100 voor bedragtype P")); }

        // Actions
	};
}



