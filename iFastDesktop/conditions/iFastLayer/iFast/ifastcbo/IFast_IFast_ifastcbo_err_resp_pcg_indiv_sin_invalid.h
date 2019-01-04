﻿#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_resp_pcg_indiv_sin_invalid : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_resp_pcg_indiv_sin_invalid() { }
		~CIFast_IFast_ifastcbo_err_resp_pcg_indiv_sin_invalid() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_RESP_PCG_INDIV_SIN_INVALID")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("RESP PCG Individual's SIN is invalid.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le NAS individuel du responsable principal REEE est invalide.")); }

        // Actions
	};
}



