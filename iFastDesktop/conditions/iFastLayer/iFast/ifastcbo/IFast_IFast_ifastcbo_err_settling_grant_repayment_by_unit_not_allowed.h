#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_settling_grant_repayment_by_unit_not_allowed : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_settling_grant_repayment_by_unit_not_allowed() { }
		~CIFast_IFast_ifastcbo_err_settling_grant_repayment_by_unit_not_allowed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_SETTLING_GRANT_REPAYMENT_BY_UNIT_NOT_ALLOWED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Settling grant repayment by units is not allowed.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le réglage du remboursement de subvention avec des unités n'est pas autorisé.")); }

        // Actions
	};
}



