#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_date_cannot_earlier_than_current_business_date : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_date_cannot_earlier_than_current_business_date() { }
		~CIFast_IFast_ifastcbo_err_date_cannot_earlier_than_current_business_date() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_DATE_CANNOT_EARLIER_THAN_CURRENT_BUSINESS_DATE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Date must not be earlier than current business date.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Date must not be earlier than current business date.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Date must not be earlier than current business date.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La date ne doit pas être antérieure à la date opérationnelle actuelle.")); }

        // Actions
	};
}



