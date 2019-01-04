#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_warn_acct_assigned_committee_powerattny : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_warn_acct_assigned_committee_powerattny() { }
		~CIFast_IFast_ifastcbo_err_warn_acct_assigned_committee_powerattny() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_WARN_ACCT_ASSIGNED_COMMITTEE_POWERATTNY")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Entire Account is assigned for reason of Committee/Power of Attorney.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Gesamtes Konto aufgrund von Vormund/ Vollmacht zugewiesen")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Se ha cedido toda la cuenta en virtud de Comité/Poder legal")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le compte est entièrement mis en garantie en raison d'un curateur/d'une procuration.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Volledige account is toegewezen vanwege curator/volmacht")); }

        // Actions
	};
}



