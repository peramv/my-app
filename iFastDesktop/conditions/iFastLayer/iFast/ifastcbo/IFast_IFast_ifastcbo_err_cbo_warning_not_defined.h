#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_cbo_warning_not_defined : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_cbo_warning_not_defined() { }
		~CIFast_IFast_ifastcbo_err_cbo_warning_not_defined() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_CBO_WARNING_NOT_DEFINED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Warning has not been defined in Desktop.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Warning has not been defined in Desktop.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'avertissement n'a pas été défini dans le bureau.")); }

        // Actions
	};
}



