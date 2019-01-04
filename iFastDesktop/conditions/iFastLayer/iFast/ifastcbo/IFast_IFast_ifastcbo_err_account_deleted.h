#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_account_deleted : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_account_deleted() { }
		~CIFast_IFast_ifastcbo_err_account_deleted() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ACCOUNT_DELETED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The account has a deleted status.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("The account has a deleted status.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("The account has a deleted status.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le statut du compte est Supprimé.")); }

        // Actions
	};
}



