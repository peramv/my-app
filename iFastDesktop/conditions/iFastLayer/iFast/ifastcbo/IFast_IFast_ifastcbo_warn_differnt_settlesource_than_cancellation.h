﻿#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_differnt_settlesource_than_cancellation : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_differnt_settlesource_than_cancellation() { }
		~CIFast_IFast_ifastcbo_warn_differnt_settlesource_than_cancellation() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_DIFFERNT_SETTLESOURCE_THAN_CANCELLATION")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Settlement Source of Cancellation and Rebook are different.")); }

        // Actions
	};
}



