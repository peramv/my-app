#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_ifastcbo_err_tax_type_no_non_register : public CConditionObject
	{
	public:
		CIFast_Infrastructure_ifastcbo_err_tax_type_no_non_register() { }
		~CIFast_Infrastructure_ifastcbo_err_tax_type_no_non_register() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_TAX_TYPE_NO_NON_REGISTER")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The zip code is not numeric.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("The zip code is not numeric.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Die Postleitzahl ist nicht nummerisch.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El código postal no es numérico.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le code postal n'est pas numérique.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("De postcode is niet numeriek")); }

        // Actions
	};
}



