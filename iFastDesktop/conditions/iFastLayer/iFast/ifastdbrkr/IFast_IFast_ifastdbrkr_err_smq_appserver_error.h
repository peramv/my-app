#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_smq_appserver_error : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_smq_appserver_error() { }
		~CIFast_IFast_ifastdbrkr_err_smq_appserver_error() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_SMQ_APPSERVER_ERROR")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("An iFAST Database Application error has occurred.\nReference: %trackid%.\n\n%msg%")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Une erreur d'application de la base de données iFAST s'est produite. \nRéférence : %trackid%. \n\n%msg%")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Please contact System support.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Veuillez communiquer avec le soutien informatique.")); }
	};
}



