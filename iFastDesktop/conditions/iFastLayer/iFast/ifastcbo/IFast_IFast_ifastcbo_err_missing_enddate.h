#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_missing_enddate : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_missing_enddate() { }
		~CIFast_IFast_ifastcbo_err_missing_enddate() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_MISSING_ENDDATE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Missing End Date.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Missing End Date.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Date de fin manquante")); }

        // Actions
	};
}



