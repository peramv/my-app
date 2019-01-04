﻿#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_cancellation_calc_eusd_failed_acctive_owner_not_found : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_cancellation_calc_eusd_failed_acctive_owner_not_found() { }
		~CIFast_IFast_ifastdbrkr_err_cancellation_calc_eusd_failed_acctive_owner_not_found() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_CANCELLATION_CALC_EUSD_FAILED_ACCTIVE_OWNER_NOT_FOUND")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Cannot calculate EUSD. No active owner found.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Impossible de calculer l'EUSD. Aucun titulaire actif trouvé.")); }

        // Actions
	};
}



