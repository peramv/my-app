#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_one_fs_alt_account : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_one_fs_alt_account() { }
		~CIFast_IFast_ifastcbo_err_one_fs_alt_account() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ONE_FS_ALT_ACCOUNT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Only one Additional Account Number is allowed per  Fund Sponsor.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Un seul numéro de compte supplémentaire est autorisé par promoteur de fonds.")); }

        // Actions
	};
}



