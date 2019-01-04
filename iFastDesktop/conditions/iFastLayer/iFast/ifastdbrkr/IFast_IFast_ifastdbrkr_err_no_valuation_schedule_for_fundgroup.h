#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_no_valuation_schedule_for_fundgroup : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_no_valuation_schedule_for_fundgroup() { }
		~CIFast_IFast_ifastdbrkr_err_no_valuation_schedule_for_fundgroup() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NO_VALUATION_SCHEDULE_FOR_FUNDGROUP")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("No valuation schedule setup for the fund group")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Aucun tableau d'évaluation n'a été réglé pour le groupe du fonds.")); }

        // Actions
	};
}



