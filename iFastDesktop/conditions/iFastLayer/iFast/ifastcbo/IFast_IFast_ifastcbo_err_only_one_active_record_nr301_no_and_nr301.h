#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_only_one_active_record_nr301_no_and_nr301 : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_only_one_active_record_nr301_no_and_nr301() { }
		~CIFast_IFast_ifastcbo_err_only_one_active_record_nr301_no_and_nr301() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ONLY_ONE_ACTIVE_RECORD_NR301_NO_AND_NR301")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Only one record should be active for NR301 and NR301 No.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Un seul enregistrement actif devrait correspondre au numéro inscrit sur les formulaires NR301 et NR301 No.")); }

        // Actions
	};
}



