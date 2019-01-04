#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_exempt_type_not_valid_for_account_type_and_designation : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_exempt_type_not_valid_for_account_type_and_designation() { }
		~CIFast_IFast_ifastcbo_err_exempt_type_not_valid_for_account_type_and_designation() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_EXEMPT_TYPE_NOT_VALID_FOR_ACCOUNT_TYPE_AND_DESIGNATION")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Exempt type not valid for account type: %accttype%, and designation: %acctdesignation%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Type d'exemption invalide pour le type de compte %accttype% et la désignation %acctdesignation%")); }

        // Actions
	};
}



