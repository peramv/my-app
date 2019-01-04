#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_fund_fee_detail_not_exist : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_fund_fee_detail_not_exist() { }
		~CIFast_IFast_ifastcbo_err_fund_fee_detail_not_exist() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FUND_FEE_DETAIL_NOT_EXIST")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Fund Fee Detail does not exist.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Fund Fee Detail does not exist.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Fund Fee Detail does not exist.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les détails des frais du fonds n'existent pas.")); }

        // Actions
	};
}



