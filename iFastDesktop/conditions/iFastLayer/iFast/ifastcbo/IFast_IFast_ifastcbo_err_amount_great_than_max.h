#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_amount_great_than_max : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_amount_great_than_max() { }
		~CIFast_IFast_ifastcbo_err_amount_great_than_max() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_AMOUNT_GREAT_THAN_MAX")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Amount must not be greater than Maximum.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Zahlungsbeträge dürfen nicht größer als das Jährliche Maximum sein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El monto de pago no debe ser mayor que el máximo anual.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le montant ne peut être supérieur au maximum.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Betalingsbedragen mogen niet groter zijn dan het jaarlijks maximum")); }

        // Actions
	};
}



