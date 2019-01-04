#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_ifastcbo_err_acct_type_not_valid_for_tax_type : public CConditionObject
	{
	public:
		CIFast_Infrastructure_ifastcbo_err_acct_type_not_valid_for_tax_type() { }
		~CIFast_Infrastructure_ifastcbo_err_acct_type_not_valid_for_tax_type() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ACCT_TYPE_NOT_VALID_FOR_TAX_TYPE")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("KYC data not found")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("KYC data not found")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("KYC data not found")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Données du profil d'investisseur introuvables")); }

        // Actions
	};
}



