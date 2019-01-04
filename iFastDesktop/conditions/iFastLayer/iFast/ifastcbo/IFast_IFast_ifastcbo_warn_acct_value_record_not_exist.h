#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_acct_value_record_not_exist : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_acct_value_record_not_exist() { }
		~CIFast_IFast_ifastcbo_warn_acct_value_record_not_exist() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_ACCT_VALUE_RECORD_NOT_EXIST")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Account Value record does not exist.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Account Value record does not exist.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Account Value record does not exist.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'enregistrement de la valeur du compte n'existe pas.")); }

        // Actions
	};
}



