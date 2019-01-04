#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_ams_active_certs_exist : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_ams_active_certs_exist() { }
		~CIFast_IFast_ifastdbrkr_err_ams_active_certs_exist() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_AMS_ACTIVE_CERTS_EXIST")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Account has active certificate units on fund %FUNDCODE%")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Un contrat actif existe.")); }

        // Actions
	};
}



