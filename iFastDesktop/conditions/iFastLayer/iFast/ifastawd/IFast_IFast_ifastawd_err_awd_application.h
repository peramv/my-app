#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastawd_err_awd_application : public CConditionObject
	{
	public:
		CIFast_IFast_ifastawd_err_awd_application() { }
		~CIFast_IFast_ifastawd_err_awd_application() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_AWD_APPLICATION")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastawd")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("An error occured in the AWD application.  Check if AWD is running.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("An error occured in the AWD application.  Check if AWD is running.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Une erreur s'est produite dans l'application AWD. Vérifiez si AWD est en cours d'exécution.")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Report the error to an administrator.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Report the error to an administrator.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Signalez l'erreur à un administrateur.")); }
	};
}



