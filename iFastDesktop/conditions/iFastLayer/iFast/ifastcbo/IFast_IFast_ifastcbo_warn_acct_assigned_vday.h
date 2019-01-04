#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_acct_assigned_vday : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_acct_assigned_vday() { }
		~CIFast_IFast_ifastcbo_warn_acct_assigned_vday() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_ACCT_ASSIGNED_VDAY")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Account assigned for reason of V-Day shares.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Account assigned for reason of V-Day shares.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Account assigned for reason of V-Day shares.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Compte mis en garantie en raison des parts au jour d'évaluation")); }

        // Actions
	};
}



