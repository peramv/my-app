#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_invalid_mrs_account : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_invalid_mrs_account() { }
		~CIFast_IFast_ifastdbrkr_err_invalid_mrs_account() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_MRS_ACCOUNT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid MRS Account.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Invalid MRS Account.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Ungültiges MRS-Konto")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Cuenta MRS no válida")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Compte MRS invalide")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Ongeldig MRS-account")); }

        // Actions
	};
}



