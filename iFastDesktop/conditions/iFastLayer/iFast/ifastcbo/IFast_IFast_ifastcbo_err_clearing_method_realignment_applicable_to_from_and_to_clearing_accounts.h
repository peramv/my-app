#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_clearing_method_realignment_applicable_to_from_and_to_clearing_accounts : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_clearing_method_realignment_applicable_to_from_and_to_clearing_accounts() { }
		~CIFast_IFast_ifastcbo_err_clearing_method_realignment_applicable_to_from_and_to_clearing_accounts() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_CLEARING_METHOD_REALIGNMENT_APPLICABLE_TO_FROM_AND_TO_CLEARING_ACCOUNTS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Realignment Method is applicable when both From and To Account are Clearing Accounts")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Realignment Method is applicable when both From and To Account are Clearing Accounts")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Realignment Method is applicable when both From and To Account are Clearing Accounts")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La méthode de réalignement est applicable lorsque les comptes source et cible sont tous deux des comptes de compensation.")); }

        // Actions
	};
}



