#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_rdsp_grant_return_cannot_be_greater_than_grant_purchase : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_rdsp_grant_return_cannot_be_greater_than_grant_purchase() { }
		~CIFast_IFast_ifastcbo_err_rdsp_grant_return_cannot_be_greater_than_grant_purchase() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_RDSP_GRANT_RETURN_CANNOT_BE_GREATER_THAN_GRANT_PURCHASE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Grant Return amount cannot be greater than the grant purchase amount.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Grant Return amount cannot be greater than the grant purchase amount.")); }

        // Actions
	};
}



