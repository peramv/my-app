#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_paternal_maternal_names_both_blank : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_paternal_maternal_names_both_blank() { }
		~CIFast_IFast_ifastcbo_err_paternal_maternal_names_both_blank() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_PATERNAL_MATERNAL_NAMES_BOTH_BLANK")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Both Paternal and Maternal Names are blank.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les noms paternels et maternels sont vides.")); }

        // Actions
	};
}
