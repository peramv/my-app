#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_smq_broken_appserver_connection : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_smq_broken_appserver_connection() { }
		~CIFast_IFast_ifastdbrkr_err_smq_broken_appserver_connection() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_SMQ_BROKEN_APPSERVER_CONNECTION")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("A communication error has occured.\nReference: %trackid%.\n\n%msg%")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Une erreur de communication s'est produite. \nRéférence : %trackid%. \n\n%msg%")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Please retry the operation.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Veuillez réessayer l'opération.")); }
	};
}



