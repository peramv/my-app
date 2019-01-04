#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_smq_message_send_failed : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_smq_message_send_failed() { }
		~CIFast_IFast_ifastdbrkr_err_smq_message_send_failed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_SMQ_MESSAGE_SEND_FAILED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Could not send message")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Impossible d'envoyer le message.")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Please contact System Support")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Veuillez communiquer avec le soutien informatique.")); }
	};
}



