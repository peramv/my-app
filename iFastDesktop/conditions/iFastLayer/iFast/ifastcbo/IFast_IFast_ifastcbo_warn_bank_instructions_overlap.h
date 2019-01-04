#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_bank_instructions_overlap : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_bank_instructions_overlap() { }
		~CIFast_IFast_ifastcbo_warn_bank_instructions_overlap() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_BANK_INSTRUCTIONS_OVERLAP")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Bank instructions for %accusage% and %cur% overlap.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Bank instructions for %accusage% and %cur% overlap.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les instructions bancaires pour %accusage% et %cur% se chevauchent.")); }

        // Actions
	};
}



