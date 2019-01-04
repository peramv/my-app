#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_tik_with_guarantee_override_same_fund_class : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_tik_with_guarantee_override_same_fund_class() { }
		~CIFast_IFast_ifastcbo_err_tik_with_guarantee_override_same_fund_class() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_TIK_WITH_GUARANTEE_OVERRIDE_SAME_FUND_CLASS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Transfer In Kind with guarantee override allowed for same fund\\class only.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le transfert en nature avec modification de garantie n'est autorisé que pour le même fonds/la même classe.")); }

        // Actions
	};
}



