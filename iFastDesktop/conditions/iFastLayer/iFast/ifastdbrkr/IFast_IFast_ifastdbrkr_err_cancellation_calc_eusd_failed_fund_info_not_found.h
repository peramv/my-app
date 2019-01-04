#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_cancellation_calc_eusd_failed_fund_info_not_found : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_cancellation_calc_eusd_failed_fund_info_not_found() { }
		~CIFast_IFast_ifastdbrkr_err_cancellation_calc_eusd_failed_fund_info_not_found() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_CANCELLATION_CALC_EUSD_FAILED_FUND_INFO_NOT_FOUND")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Cannot calculate EUSD. Fund master/info is not found.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Impossible de calculer l'EUSD. L'original du fonds/l'information sur le fonds est introuvable.")); }

        // Actions
	};
}



