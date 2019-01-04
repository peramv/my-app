#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_smq_no_appserver : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_smq_no_appserver() { }
		~CIFast_IFast_ifastdbrkr_err_smq_no_appserver() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_SMQ_NO_APPSERVER")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The Application Server for this database is unavailable.\nReference: %trackid%.\n\n%msg%")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le serveur d'application pour cette base de données n'est pas disponible. \n Référence : %trackid%. \n\n %msg%.")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Please retry later.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Veuillez réessayer plus tard.")); }
	};
}



