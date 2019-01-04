#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_rdsp_external_contract_mandatory : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_rdsp_external_contract_mandatory() { }
		~CIFast_IFast_ifastcbo_warn_rdsp_external_contract_mandatory() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_RDSP_EXTERNAL_CONTRACT_MANDATORY")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("External RDSP Account Contract Number is mandatory.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("External RDSP Account Contract Number is mandatory.")); }

        // Actions
	};
}



