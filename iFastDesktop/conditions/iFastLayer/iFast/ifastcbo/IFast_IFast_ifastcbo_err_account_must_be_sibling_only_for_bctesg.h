#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_account_must_be_sibling_only_for_bctesg : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_account_must_be_sibling_only_for_bctesg() { }
		~CIFast_IFast_ifastcbo_err_account_must_be_sibling_only_for_bctesg() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ACCOUNT_MUST_BE_SIBLING_ONLY_FOR_BCTESG")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Account must be Sibling Only for BCTESG.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Compte de frère et sœur seulement pour la SEEEFCB.")); }


        // Actions
	};
}



