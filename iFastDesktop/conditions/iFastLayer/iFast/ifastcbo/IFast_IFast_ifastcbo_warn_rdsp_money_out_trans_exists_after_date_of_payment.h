#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_rdsp_money_out_trans_exists_after_date_of_payment : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_rdsp_money_out_trans_exists_after_date_of_payment() { }
		~CIFast_IFast_ifastcbo_warn_rdsp_money_out_trans_exists_after_date_of_payment() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_RDSP_MONEY_OUT_TRANS_EXISTS_AFTER_DATE_OF_PAYMENT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Money Out Transactions exist after Date of Payment.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Money Out Transactions exist after Date of Payment.")); }

        // Actions
	};
}



