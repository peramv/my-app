#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_no_bussiness_day_record_avail : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_no_bussiness_day_record_avail() { }
		~CIFast_IFast_ifastdbrkr_err_no_bussiness_day_record_avail() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NO_BUSSINESS_DAY_RECORD_AVAIL")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("No business day record available.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Aucun enregistrement de jour ouvrable n'est disponible.")); }

        // Actions
	};
}



