#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_qesi_increase_limit_exceeded_for_year : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_qesi_increase_limit_exceeded_for_year() { }
		~CIFast_IFast_ifastcbo_warn_qesi_increase_limit_exceeded_for_year() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_QESI_INCREASE_LIMIT_EXCEEDED_FOR_YEAR")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("QESI Increase Limit exceeded for the year.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Limite d'IQEE majoré excédée pour l'année")); }

        // Actions
	};
}



