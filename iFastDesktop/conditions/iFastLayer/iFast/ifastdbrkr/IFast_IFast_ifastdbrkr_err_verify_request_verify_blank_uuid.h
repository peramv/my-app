#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_verify_request_verify_blank_uuid : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_verify_request_verify_blank_uuid() { }
		~CIFast_IFast_ifastdbrkr_err_verify_request_verify_blank_uuid() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_VERIFY_REQUEST_VERIFY_BLANK_UUID")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("VerifyRequest - VerifyUUID is blank")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Demande de vérification – le champ UU de lien de vérification est vide.")); }

        // Actions
	};
}



