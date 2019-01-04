#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_from_to_classes_not_belong_to_same_fund : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_from_to_classes_not_belong_to_same_fund() { }
		~CIFast_IFast_ifastcbo_err_from_to_classes_not_belong_to_same_fund() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FROM_TO_CLASSES_NOT_BELONG_TO_SAME_FUND")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Classes involved in the transaction do not belong to same Fund.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les classes touchées par la transaction n'appartiennent pas au même fonds.")); }

        // Actions
	};
}



