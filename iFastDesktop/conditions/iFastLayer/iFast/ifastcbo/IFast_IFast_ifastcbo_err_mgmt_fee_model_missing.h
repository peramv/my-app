﻿#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_mgmt_fee_model_missing : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_mgmt_fee_model_missing() { }
		~CIFast_IFast_ifastcbo_err_mgmt_fee_model_missing() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_MGMT_FEE_MODEL_MISSING")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Management fee model is missing.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le modèle de frais de gestion est manquant.")); }

        // Actions
	};
}



