#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_date_earlier_than_current_bus_day : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_date_earlier_than_current_bus_day() { }
		~CIFast_IFast_ifastcbo_err_date_earlier_than_current_bus_day() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_DATE_EARLIER_THAN_CURRENT_BUS_DAY")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Date earlier then Current Business Date.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Date earlier then Current Business Date.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Date earlier then Current Business Date.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La date est antérieure à la date opérationnelle actuelle.")); }

        // Actions
	};
}



