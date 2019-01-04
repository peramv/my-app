#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_non_receipt_flag_active : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_non_receipt_flag_active() { }
		~CIFast_IFast_ifastcbo_err_non_receipt_flag_active() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NON_RECEIPT_FLAG_ACTIVE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Transaction includes units for which receipt is outstanding on %FUND%/%CLASS%")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La transaction comprend des unités dont le reçu est en suspens pour %FUND%/%CLASS%.")); }

        // Actions
	};
}



