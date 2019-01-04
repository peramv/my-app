#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_not_enough_grant_amt_return : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_not_enough_grant_amt_return() { }
		~CIFast_IFast_ifastdbrkr_err_not_enough_grant_amt_return() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NOT_ENOUGH_GRANT_AMT_RETURN")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Not enough grant amount for return.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Nicht genug Zuschuss für Rendite.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Not enough grant amount for return.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Montant de subvention insuffisant pour le remboursement")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Not enough grant amount for return")); }

        // Actions
	};
}



