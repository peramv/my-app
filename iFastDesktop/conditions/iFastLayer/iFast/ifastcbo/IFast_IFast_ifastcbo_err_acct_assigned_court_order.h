#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_acct_assigned_court_order : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_acct_assigned_court_order() { }
		~CIFast_IFast_ifastcbo_err_acct_assigned_court_order() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ACCT_ASSIGNED_COURT_ORDER")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Account assigned for reason of court order.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Account assigned for reason of court order.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Account assigned for reason of court order.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Compte mis en garantie en raison d'une ordonnance du tribunal")); }

        // Actions
	};
}



