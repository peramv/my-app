#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_adjustment_required : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_adjustment_required() { }
		~CIFast_IFast_ifastcbo_err_adjustment_required() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ADJUSTMENT_REQUIRED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Adjustment may be required.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Un ajustement pourrait être requis.")); }

        // Actions
	};
}



