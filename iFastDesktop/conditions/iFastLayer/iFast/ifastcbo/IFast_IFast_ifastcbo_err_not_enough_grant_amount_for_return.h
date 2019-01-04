#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_not_enough_grant_amount_for_return : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_not_enough_grant_amount_for_return() { }
		~CIFast_IFast_ifastcbo_err_not_enough_grant_amount_for_return() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NOT_ENOUGH_GRANT_AMOUNT_FOR_RETURN")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Not enough grant amount for return.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Montant de subvention insuffisant pour un remboursement")); }

        // Actions
	};
}



