#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_reference_no_is_mandatory_for_source_of_fund : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_reference_no_is_mandatory_for_source_of_fund() { }
		~CIFast_IFast_ifastcbo_err_reference_no_is_mandatory_for_source_of_fund() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_REFERENCE_NO_IS_MANDATORY_FOR_SOURCE_OF_FUND")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Reference no. is mandatory for this Source of Fund.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le numéro de référence est requis pour cette source de fonds.")); }

        // Actions
	};
}



