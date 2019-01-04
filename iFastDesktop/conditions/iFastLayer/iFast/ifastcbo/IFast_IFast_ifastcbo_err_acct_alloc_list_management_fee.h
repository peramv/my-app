#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_acct_alloc_list_management_fee : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_acct_alloc_list_management_fee() { }
		~CIFast_IFast_ifastcbo_err_acct_alloc_list_management_fee() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ACCT_ALLOC_LIST_MANAGEMENT_FEE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Only one account should be defined for Management Fee.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Only one account should be defined for Management Fee.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Only one account should be defined for Management Fee.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Un seul compte devrait être défini pour les frais de gestion.")); }

        // Actions
	};
}



