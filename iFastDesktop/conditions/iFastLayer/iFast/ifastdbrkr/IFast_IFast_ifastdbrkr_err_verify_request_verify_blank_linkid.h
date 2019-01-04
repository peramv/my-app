#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_verify_request_verify_blank_linkid : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_verify_request_verify_blank_linkid() { }
		~CIFast_IFast_ifastdbrkr_err_verify_request_verify_blank_linkid() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_VERIFY_REQUEST_VERIFY_BLANK_LINKID")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("VerifyRequest - VerifyLinkID is blank")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Demande de vérification – le champ de code de lien de vérification est vide.")); }

        // Actions
	};
}



