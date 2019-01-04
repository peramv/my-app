#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_smq_message_receive_failed : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_smq_message_receive_failed() { }
		~CIFast_IFast_ifastdbrkr_err_smq_message_receive_failed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_SMQ_MESSAGE_RECEIVE_FAILED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("An attempt to receive a message failed")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Échec de tentative de réception d'un message")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Please contact System Support")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Veuillez communiquer avec le soutien informatique.")); }
	};
}



