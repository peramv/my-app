#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_rdsp_external_plan_mandatory : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_rdsp_external_plan_mandatory() { }
		~CIFast_IFast_ifastcbo_err_rdsp_external_plan_mandatory() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_RDSP_EXTERNAL_PLAN_MANDATORY")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("External RDSP Specimen Plan Number is mandatory.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("External RDSP Specimen Plan Number is mandatory.")); }

        // Actions
	};
}



