#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_pf_crystalisation_is_not_yet_completed_for_fundclass : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_pf_crystalisation_is_not_yet_completed_for_fundclass() { }
		~CIFast_IFast_ifastdbrkr_err_pf_crystalisation_is_not_yet_completed_for_fundclass() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_PF_CRYSTALISATION_IS_NOT_YET_COMPLETED_FOR_FUNDCLASS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("PF Crystalisation is not yet completed for Fund-Class.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("PF Crystalisation is not yet completed for Fund-Class.")); }

        // Actions
	};
}



