#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_fund_not_eligible_for_mgmt_fee : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_fund_not_eligible_for_mgmt_fee() { }
		~CIFast_IFast_ifastcbo_err_fund_not_eligible_for_mgmt_fee() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FUND_NOT_ELIGIBLE_FOR_MGMT_FEE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Fund is not eligible for management fee trading.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Fund is not eligible for management fee trading.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le fonds n'est pas admissible aux opérations de frais de gestion.")); }

        // Actions
	};
}



