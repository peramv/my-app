#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_rdsp_relationship_to_beneficiary_required : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_rdsp_relationship_to_beneficiary_required() { }
		~CIFast_IFast_ifastcbo_warn_rdsp_relationship_to_beneficiary_required() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_RDSP_RELATIONSHIP_TO_BENEFICIARY_REQUIRED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Relationship between Accountholder and RDSP Beneficiary must be specified.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Relationship between Accountholder and RDSP Beneficiary must be specified.")); }

        // Actions
	};
}



