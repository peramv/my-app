#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_smq_sonicmq_error : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_smq_sonicmq_error() { }
		~CIFast_IFast_ifastdbrkr_err_smq_sonicmq_error() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_SMQ_SONICMQ_ERROR")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("A communication error has occured.\nReference: %ERROR%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Une erreur de communication s'est produite. \nRéférence : %ERROR%.")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Please restart Desktop and try again. If the problem still occurs then please contact System support.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Veuillez communiquer avec le soutien informatique.")); }
	};
}



