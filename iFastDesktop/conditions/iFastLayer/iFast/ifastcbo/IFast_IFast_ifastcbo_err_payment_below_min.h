#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_payment_below_min : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_payment_below_min() { }
		~CIFast_IFast_ifastcbo_err_payment_below_min() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_PAYMENT_BELOW_MIN")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Payment Amount is below minimum.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Zahlungsbetrag liegt unter dem Minimum.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El monto de pago se encuentra por debajo del mínimo.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le montant du paiement est inférieur au minimum.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Betalingsbedrag ligt onder het minimum")); }

        // Actions
	};
}



