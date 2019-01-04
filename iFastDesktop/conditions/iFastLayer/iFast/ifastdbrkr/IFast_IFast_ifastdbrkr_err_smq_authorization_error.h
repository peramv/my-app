#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_smq_authorization_error : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_smq_authorization_error() { }
		~CIFast_IFast_ifastdbrkr_err_smq_authorization_error() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_SMQ_AUTHORIZATION_ERROR")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The Middleware Framework is reporting an authorization problem:\n%msg%")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Un problème d’autorisation a été communiqué par le réseau intermédiaire : \n %msg%.")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Please contact System support.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Veuillez communiquer avec le soutien informatique.")); }
	};
}



