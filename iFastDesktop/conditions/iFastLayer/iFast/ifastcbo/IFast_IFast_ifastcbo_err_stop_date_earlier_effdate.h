#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_stop_date_earlier_effdate : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_stop_date_earlier_effdate() { }
		~CIFast_IFast_ifastcbo_err_stop_date_earlier_effdate() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_STOP_DATE_EARLIER_EFFDATE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Stop Date is earlier than Effective Date.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La date d'arrêt est antérieure à la date d'entrée en vigueur.")); }

        // Actions
	};
}



