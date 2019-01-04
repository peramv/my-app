#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_rdsp_ldap_invalid_repayment_reason : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_rdsp_ldap_invalid_repayment_reason() { }
		~CIFast_IFast_ifastcbo_warn_rdsp_ldap_invalid_repayment_reason() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_RDSP_LDAP_INVALID_REPAYMENT_REASON")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Repayment reason does not match for LDAP.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Repayment reason does not match for LDAP.")); }

        // Actions
	};
}



