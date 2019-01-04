#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_pre_yr_percent : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_pre_yr_percent() { }
		~CIFast_IFast_ifastcbo_err_pre_yr_percent() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_PRE_YR_PERCENT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The value for previous year percentage must be between 0 and 100.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("The value for previous year percentage must be between 0 and 100.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("The value for previous year percentage must be between 0 and 100.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La valeur du pourcentage de l'année précédente doit être située entre 0 et 100.")); }

        // Actions
	};
}



