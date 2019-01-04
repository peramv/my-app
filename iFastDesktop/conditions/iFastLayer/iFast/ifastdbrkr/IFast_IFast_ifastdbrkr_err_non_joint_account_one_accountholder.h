#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_non_joint_account_one_accountholder : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_non_joint_account_one_accountholder() { }
		~CIFast_IFast_ifastdbrkr_err_non_joint_account_one_accountholder() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NON_JOINT_ACCOUNT_ONE_ACCOUNTHOLDER")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Non-joint Account may have only one Accountholder.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Non-joint Account may have only one Accountholder.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Non-joint-Konto hat eventuell nur einen Kontoinhaber")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Las cuentas no conjuntas sólo pueden tener un titular")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Un compte non conjoint ne peut avoir qu'un titulaire de compte.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Niet-gezamenlijk account kan slechts één accounthouder hebben")); }

        // Actions
	};
}



