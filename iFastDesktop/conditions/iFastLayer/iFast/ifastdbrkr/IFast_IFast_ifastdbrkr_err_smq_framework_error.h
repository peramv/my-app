#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_smq_framework_error : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_smq_framework_error() { }
		~CIFast_IFast_ifastdbrkr_err_smq_framework_error() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_SMQ_FRAMEWORK_ERROR")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("An error has been detected in the Middleware Framework.\nReference: %trackid%.\n\n%msg%")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Une erreur a été identifiée dans le réseau intermédiaire.\n Référence : %trackid%. \n\n %msg%")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Copy details using the menu command and contact support.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Copiez les détails en utilisant la commande du menu et communiquez avec le soutien informatique.")); }
	};
}



