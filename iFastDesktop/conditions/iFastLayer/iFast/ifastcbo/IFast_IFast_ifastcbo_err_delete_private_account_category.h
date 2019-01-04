#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_delete_private_account_category : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_delete_private_account_category() { }
		~CIFast_IFast_ifastcbo_err_delete_private_account_category() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_DELETE_PRIVATE_ACCOUNT_CATEGORY")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The account is marked as private. Remove the flag prior to change the account type.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Ce compte est marqué comme privé. Retirez ce signal avant de changer le type de compte.")); }

        // Actions
	};
}



