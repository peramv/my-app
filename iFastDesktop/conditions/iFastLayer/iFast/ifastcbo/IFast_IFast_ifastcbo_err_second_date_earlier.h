#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_second_date_earlier : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_second_date_earlier() { }
		~CIFast_IFast_ifastcbo_err_second_date_earlier() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_SECOND_DATE_EARLIER")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("To Date is earlier than From Date.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("To Date is earlier than From Date.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("To Date is earlier than From Date.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La date cible est antérieure à la date source.")); }

        // Actions
	};
}



