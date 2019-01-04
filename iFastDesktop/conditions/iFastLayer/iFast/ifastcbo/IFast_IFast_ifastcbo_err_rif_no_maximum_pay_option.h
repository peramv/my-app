#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_rif_no_maximum_pay_option : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_rif_no_maximum_pay_option() { }
		~CIFast_IFast_ifastcbo_err_rif_no_maximum_pay_option() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_RIF_NO_MAXIMUM_PAY_OPTION")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Maximum pay option is not allowed.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Maximum pay option is not allowed.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Die Zahlungsoption \"X\"(Maximum) ist nicht erlaubt.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se permite la opción de pago \"X\" (máximo).")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'option de paiement maximum n'est pas autorisée.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Betalingsoptie 'X' (maximum) is niet toegestaan")); }

        // Actions
	};
}



