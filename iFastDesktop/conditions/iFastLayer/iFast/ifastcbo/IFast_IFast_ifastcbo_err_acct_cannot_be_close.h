#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_acct_cannot_be_close : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_acct_cannot_be_close() { }
		~CIFast_IFast_ifastcbo_err_acct_cannot_be_close() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ACCT_CANNOT_BE_CLOSE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Account cannot be closed. Account values exist after this date.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Account cannot be closed. Account values exist after this date.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Account cannot be closed. Account values exist after this date.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le compte ne peut être fermé. Des valeurs du compte existent après cette date.")); }

        // Actions
	};
}



