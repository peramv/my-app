#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_business_date_only : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_business_date_only() { }
		~CIFast_IFast_ifastcbo_err_business_date_only() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_BUSINESS_DATE_ONLY")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("%DATE% must be a business date.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("%DATE% must be a business date.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("%DATE% must be a business date.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("%DATE% doit être une date opérationnelle.")); }

        // Actions
	};
}



