#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_rif_too_big_amount : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_rif_too_big_amount() { }
		~CIFast_IFast_ifastcbo_err_rif_too_big_amount() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_RIF_TOO_BIG_AMOUNT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Payment Amount must not be greater than Maximum.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Payment Amount must not be greater than Maximum.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Zahlungsbetrag darf nicht größer als das Maximum sein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El monto de pago no debe ser superior al máximo.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le montant du paiement ne doit pas excéder le maximum.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Betalingsbedrag mag niet groter zijn dan Maximum")); }

        // Actions
	};
}



