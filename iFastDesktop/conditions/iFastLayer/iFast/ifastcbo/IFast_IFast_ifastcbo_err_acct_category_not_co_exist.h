#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_acct_category_not_co_exist : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_acct_category_not_co_exist() { }
		~CIFast_IFast_ifastcbo_err_acct_category_not_co_exist() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ACCT_CATEGORY_NOT_CO_EXIST")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Account category couldn't use at the same time.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La catégorie de compte ne peut être utilisée au même moment.")); }

        // Actions
	};
}



