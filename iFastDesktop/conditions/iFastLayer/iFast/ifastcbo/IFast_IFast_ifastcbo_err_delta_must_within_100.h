#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_delta_must_within_100 : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_delta_must_within_100() { }
		~CIFast_IFast_ifastcbo_err_delta_must_within_100() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_DELTA_MUST_WITHIN_100")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Delta value must be within range of -100% to +100%.")); }
	};
}