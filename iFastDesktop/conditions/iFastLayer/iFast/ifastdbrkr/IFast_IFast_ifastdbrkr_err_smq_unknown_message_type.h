#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_smq_unknown_message_type : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_smq_unknown_message_type() { }
		~CIFast_IFast_ifastdbrkr_err_smq_unknown_message_type() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_SMQ_UNKNOWN_MESSAGE_TYPE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("An unknown message type was received")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Un type de message inconnu a été reçu.")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Please contact System Supoort")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Veuillez communiquer avec le soutien informatique.")); }
	};
}



