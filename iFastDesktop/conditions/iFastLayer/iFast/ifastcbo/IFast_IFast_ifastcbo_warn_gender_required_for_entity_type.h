#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_gender_required_for_entity_type : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_gender_required_for_entity_type() { }
		~CIFast_IFast_ifastcbo_warn_gender_required_for_entity_type() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_GENDER_REQUIRED_FOR_ENTITY_TYPE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Beneficiary's Gender is missing.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le genre du bénéficiaire est manquant.")); }

        // Actions
	};
}



