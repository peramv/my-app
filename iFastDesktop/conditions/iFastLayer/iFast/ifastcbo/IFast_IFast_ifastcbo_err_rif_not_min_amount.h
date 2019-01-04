#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_rif_not_min_amount : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_rif_not_min_amount() { }
		~CIFast_IFast_ifastcbo_err_rif_not_min_amount() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_RIF_NOT_MIN_AMOUNT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Amount must be Minimum when Pay Options is Minimum.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Amount must be Minimum when Pay Options is Minimum.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Betrag muss min sein, wenn “Zahlungsoptionen” min ist.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El monto debe ser Mín cuando Opciones de pago es Mín.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le montant doit être Minimum quand l'option de paiement est Minimum.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Bedrag moet min. zijn als Betalingsopties min. is")); }

        // Actions
	};
}



