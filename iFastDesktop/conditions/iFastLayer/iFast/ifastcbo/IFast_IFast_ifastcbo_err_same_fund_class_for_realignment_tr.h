#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_same_fund_class_for_realignment_tr : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_same_fund_class_for_realignment_tr() { }
		~CIFast_IFast_ifastcbo_err_same_fund_class_for_realignment_tr() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_SAME_FUND_CLASS_FOR_REALIGNMENT_TR")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Fund From-To and Class From-To must be the same.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'origine et la cible du fonds et l'origine et la cible de la classe doivent être les mêmes.")); }

        // Actions
	};
}



