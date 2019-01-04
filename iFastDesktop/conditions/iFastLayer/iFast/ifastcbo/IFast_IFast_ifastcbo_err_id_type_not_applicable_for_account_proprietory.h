#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_id_type_not_applicable_for_account_proprietory : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_id_type_not_applicable_for_account_proprietory() { }
		~CIFast_IFast_ifastcbo_err_id_type_not_applicable_for_account_proprietory() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ID_TYPE_NOT_APPLICABLE_FOR_ACCOUNT_PROPRIETORY")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("%ID_TYPE% is not applicable for this account.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("%ID_TYPE% ne s’applique pas à ce compte.")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Please review individual or sole propietorship of the account.")); }
	};
}



