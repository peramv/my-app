#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_pac_stop_date_restriction : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_pac_stop_date_restriction() { }
		~CIFast_IFast_ifastcbo_err_pac_stop_date_restriction() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_PAC_STOP_DATE_RESTRICTION")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("New Stop Date should be between Current Buisness Day %DATE1% and Current PAC Stop Date %DATE2% .")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La nouvelle date de fin devrait se situer entre le jour ouvrable actuel %DATE1% et la date de fin actuelle de la PAC  %DATE2%.")); }

        // Actions
	};
}



