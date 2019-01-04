#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_cut_off_time_duplicate : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_cut_off_time_duplicate() { }
		~CIFast_IFast_ifastcbo_err_cut_off_time_duplicate() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_CUT_OFF_TIME_DUPLICATE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Duplicate cut off time.  [%CODE%]")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Duplicate cut off time.  [%CODE%]")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Copie de l'heure limite [%CODE%]")); }

        // Actions
	};
}



