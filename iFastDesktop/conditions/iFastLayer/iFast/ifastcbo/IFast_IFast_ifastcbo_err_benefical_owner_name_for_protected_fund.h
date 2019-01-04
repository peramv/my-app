#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_benefical_owner_name_for_protected_fund : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_benefical_owner_name_for_protected_fund() { }
		~CIFast_IFast_ifastcbo_err_benefical_owner_name_for_protected_fund() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_BENEFICAL_OWNER_NAME_FOR_PROTECTED_FUND")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Trading of Protected Fund not allowed for beneficial owner name is missing.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Trading of Protected Fund not allowed for beneficial owner name is missing.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Trading of Protected Fund not allowed for beneficial owner name is missing.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'opération de fonds protégés n'est pas autorisée parce que le nom du titulaire bénéficiaire est manquant.")); }

        // Actions
	};
}



