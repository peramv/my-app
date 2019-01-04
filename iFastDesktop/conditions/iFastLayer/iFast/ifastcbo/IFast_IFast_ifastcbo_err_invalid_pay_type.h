#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_invalid_pay_type : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_invalid_pay_type() { }
		~CIFast_IFast_ifastcbo_err_invalid_pay_type() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_PAY_TYPE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid Payment Type when Destination Fund is CASH.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Ungültige Zahlungsart, wenn Ziel-Fonds \"Bargeld\" ist.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Tipo de pago no válido cuando el fondo de destino es EFECTIVO")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Type de paiement invalide lorsque le fonds de destination est COMPTANT")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Ongeldig betalingstype als bestemmingsfonds CONTANT is")); }

        // Actions
	};
}



