#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_todate_after_curbus_date : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_todate_after_curbus_date() { }
		~CIFast_IFast_ifastcbo_err_todate_after_curbus_date() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_TODATE_AFTER_CURBUS_DATE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("To Date cannot be after current business day.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La date cible ne peut être postérieure au jour ouvrable actuel.")); }

        // Actions
	};
}



