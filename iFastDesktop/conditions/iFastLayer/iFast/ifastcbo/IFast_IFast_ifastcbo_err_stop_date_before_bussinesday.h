#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_stop_date_before_bussinesday : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_stop_date_before_bussinesday() { }
		~CIFast_IFast_ifastcbo_err_stop_date_before_bussinesday() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_STOP_DATE_BEFORE_BUSSINESDAY")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Stop date cannot be before current business day.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La date d'arrêt ne peut être antérieure au jour ouvrable actuel.")); }

        // Actions
	};
}



