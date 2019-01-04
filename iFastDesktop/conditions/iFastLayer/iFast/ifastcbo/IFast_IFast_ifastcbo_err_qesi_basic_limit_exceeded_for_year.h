#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_qesi_basic_limit_exceeded_for_year : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_qesi_basic_limit_exceeded_for_year() { }
		~CIFast_IFast_ifastcbo_err_qesi_basic_limit_exceeded_for_year() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_QESI_BASIC_LIMIT_EXCEEDED_FOR_YEAR")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("QESI Limit exceeded for the year.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Limite atteinte pour l'IQEE de l'année.")); }

        // Actions
	};
}



