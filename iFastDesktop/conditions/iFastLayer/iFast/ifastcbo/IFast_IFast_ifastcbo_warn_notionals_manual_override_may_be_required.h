#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_notionals_manual_override_may_be_required : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_notionals_manual_override_may_be_required() { }
		~CIFast_IFast_ifastcbo_warn_notionals_manual_override_may_be_required() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_NOTIONALS_MANUAL_OVERRIDE_MAY_BE_REQUIRED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Transfer out or Grant repayment transaction exists in the account. Manual override may be required.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Un transfert sortant ou un remboursement de subvention apparaît dans le compte. Un écrasement manuel pourrait être nécessaire.")); }

        // Actions
	};
}



