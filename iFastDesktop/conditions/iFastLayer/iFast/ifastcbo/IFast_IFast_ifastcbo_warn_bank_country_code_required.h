#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_bank_country_code_required : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_bank_country_code_required() { }
		~CIFast_IFast_ifastcbo_warn_bank_country_code_required() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_BANK_COUNTRY_CODE_REQUIRED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Banking information country code is a required field.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Banking information country code is a required field.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le code du pays de l'information bancaire est requis.")); }

        // Actions
	};
}



