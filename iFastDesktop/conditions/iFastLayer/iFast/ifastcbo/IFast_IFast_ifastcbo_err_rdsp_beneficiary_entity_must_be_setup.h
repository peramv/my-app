#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_rdsp_beneficiary_entity_must_be_setup : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_rdsp_beneficiary_entity_must_be_setup() { }
		~CIFast_IFast_ifastcbo_err_rdsp_beneficiary_entity_must_be_setup() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_RDSP_BENEFICIARY_ENTITY_MUST_BE_SETUP")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("RDSP Beneficiary Entity must be setup.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("RDSP Beneficiary Entity must be setup.")); }

        // Actions
	};
}



