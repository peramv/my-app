#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_rdsp_beneficiary_dofbirth_missing : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_rdsp_beneficiary_dofbirth_missing() { }
		~CIFast_IFast_ifastcbo_err_rdsp_beneficiary_dofbirth_missing() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_RDSP_BENEFICIARY_DOFBIRTH_MISSING")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("RDSP Beneficiary's Date of Birth is missing.")); }		
		virtual DString GetMessage_FR_CA() const { return DString(I_("RDSP Beneficiary's Date of Birth is missing.")); }	

        // Actions
	};
}



