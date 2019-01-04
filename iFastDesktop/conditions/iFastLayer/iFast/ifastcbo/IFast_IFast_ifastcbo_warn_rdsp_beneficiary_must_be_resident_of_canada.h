#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_rdsp_beneficiary_must_be_resident_of_canada : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_rdsp_beneficiary_must_be_resident_of_canada() { }
		~CIFast_IFast_ifastcbo_warn_rdsp_beneficiary_must_be_resident_of_canada() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_RDSP_BENEFICIARY_MUST_BE_RESIDENT_OF_CANADA")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Beneficiary tax jurisdiction must be Canadian at the trade effective date.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Beneficiary tax jurisdiction must be Canadian at the trade effective date.")); }

        // Actions
	};
}



