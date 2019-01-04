#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_rollover_not_same_account_owner : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_rollover_not_same_account_owner() { }
		~CIFast_IFast_ifastcbo_err_rollover_not_same_account_owner() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ROLLOVER_NOT_SAME_ACCOUNT_OWNER")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Owner on To Account does not match From Account.  Ensure they match before proceeding.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Owner on To Account does not match From Account.  Ensure they match before proceeding.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le titulaire du compte compte cible ne correspond pas à celui du compte source. Assurez-vous qu'ils correspondent avant de procéder.")); }

        // Actions
	};
}



