﻿#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_dob_resp_benef_required : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_dob_resp_benef_required() { }
		~CIFast_IFast_ifastcbo_warn_dob_resp_benef_required() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_DOB_RESP_BENEF_REQUIRED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Beneficiary's Date of Birth is missing.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La date de naissance du bénéficiaire est manquante.")); }

        // Actions
	};
}



