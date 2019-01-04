#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_occupation_required : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_occupation_required() { }
		~CIFast_IFast_ifastcbo_err_occupation_required() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_OCCUPATION_REQUIRED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Occupation is a required field.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Occupation is a required field.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Occupation is a required field.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'emploi est requis.")); }

        // Actions
	};
}



