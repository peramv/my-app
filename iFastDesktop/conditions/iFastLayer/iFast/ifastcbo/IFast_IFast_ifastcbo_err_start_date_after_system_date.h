#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_start_date_after_system_date : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_start_date_after_system_date() { }
		~CIFast_IFast_ifastcbo_err_start_date_after_system_date() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_START_DATE_AFTER_SYSTEM_DATE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Start date is after system date.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La date de début est postérieure à la date système.")); }

        // Actions
	};
}



