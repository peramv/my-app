﻿#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_pse_information_required : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_pse_information_required() { }
		~CIFast_IFast_ifastcbo_err_pse_information_required() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_PSE_INFORMATION_REQUIRED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("PSE Information is required for this redemption.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Informations d'EPS est requise pour ce rachat.")); }

        // Actions
	};
}



