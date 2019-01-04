#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_warn_shareholder_younger_than_18 : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_warn_shareholder_younger_than_18() { }
		~CIFast_IFast_ifastcbo_err_warn_shareholder_younger_than_18() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_WARN_SHAREHOLDER_YOUNGER_THAN_18")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Account Owner is younger than 18 years old.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Kontoinhaber ist jünger als 18 Jahre.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El propietario de la cuenta tiene menos de 18 años.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le titulaire du compte est âgé de moins de 18 ans.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Accounthouder is jonger dan 18 jaar")); }

        // Actions
	};
}



