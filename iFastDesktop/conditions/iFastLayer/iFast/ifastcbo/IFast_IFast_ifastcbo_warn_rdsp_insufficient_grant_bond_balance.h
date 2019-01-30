#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_rdsp_insufficient_grant_bond_balance : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_rdsp_insufficient_grant_bond_balance() { }
		~CIFast_IFast_ifastcbo_warn_rdsp_insufficient_grant_bond_balance() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_RDSP_INSUFFICIENT_GRANT_BOND_BALANCE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Insufficient grant/bond balance, repayment may reject.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Insufficient grant/bond balance, repayment may reject.")); }

        // Actions
	};
}



