#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_acct_assigned_cheque_holdback : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_acct_assigned_cheque_holdback() { }
		~CIFast_IFast_ifastcbo_warn_acct_assigned_cheque_holdback() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_ACCT_ASSIGNED_CHEQUE_HOLDBACK")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Account assigned for reason of cheque holdback.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Account assigned for reason of cheque holdback.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Account assigned for reason of cheque holdback.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Compte mis en garantie en raison d'une retenue de chèque")); }

        // Actions
	};
}



