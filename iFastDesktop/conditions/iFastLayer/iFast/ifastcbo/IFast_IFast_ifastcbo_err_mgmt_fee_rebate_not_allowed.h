#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_mgmt_fee_rebate_not_allowed : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_mgmt_fee_rebate_not_allowed() { }
		~CIFast_IFast_ifastcbo_err_mgmt_fee_rebate_not_allowed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_MGMT_FEE_REBATE_NOT_ALLOWED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Management fee rebate not allowed.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Remise sur les frais de gestion non autorisée")); }

        // Actions
	};
}



