#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_contract_type_is_not_found_for_this_account : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_contract_type_is_not_found_for_this_account() { }
		~CIFast_IFast_ifastdbrkr_err_contract_type_is_not_found_for_this_account() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_CONTRACT_TYPE_IS_NOT_FOUND_FOR_THIS_ACCOUNT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Contract type not found for this account.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Contract type not found for this account.")); }

        // Actions
	};
}



