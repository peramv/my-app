#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_acct_assigned_cq : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_acct_assigned_cq() { }
		~CIFast_IFast_ifastcbo_warn_acct_assigned_cq() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_ACCT_ASSIGNED_CQ")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Account assigned for reason of advance CQ/EFT payment.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Account assigned for reason of advance CQ/EFT payment.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Account assigned for reason of advance CQ/EFT payment.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Compte mis en garantie en raison d'un paiement par chèque/TEF anticipé")); }

        // Actions
	};
}



