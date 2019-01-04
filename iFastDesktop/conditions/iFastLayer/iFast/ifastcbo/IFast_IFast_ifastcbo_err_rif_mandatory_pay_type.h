#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_rif_mandatory_pay_type : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_rif_mandatory_pay_type() { }
		~CIFast_IFast_ifastcbo_err_rif_mandatory_pay_type() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_RIF_MANDATORY_PAY_TYPE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("It is mandatory to insert a value for Pay Type.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("It is mandatory to insert a value for Pay Type.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Die Eingabe eines Wertes für Zahlungsart ist obligatorisch.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Es obligatorio insertar un valor para el tipo de pago.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le type de paiement est requis.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Het is verplicht om een waarde in te vullen bij Betalingstype")); }

        // Actions
	};
}



