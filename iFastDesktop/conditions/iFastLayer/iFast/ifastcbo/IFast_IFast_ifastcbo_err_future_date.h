#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_future_date : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_future_date() { }
		~CIFast_IFast_ifastcbo_err_future_date() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FUTURE_DATE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Future dates are not allowed for %FieldName%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les dates à venir ne sont pas autorisées pour %FieldName%.")); }

        // Actions
	};
}



