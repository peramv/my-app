#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_annuitants_for_from_to_must_be_the_same : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_annuitants_for_from_to_must_be_the_same() { }
		~CIFast_IFast_ifastcbo_err_annuitants_for_from_to_must_be_the_same() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ANNUITANTS_FOR_FROM_TO_MUST_BE_THE_SAME")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The annuitants for the From and To account must be the same.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("The annuitants for the From and To account must be the same.")); }

        // Actions
	};
}