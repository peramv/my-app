#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_fund_group_not_exist_for_management_fee : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_fund_group_not_exist_for_management_fee() { }
		~CIFast_IFast_ifastcbo_err_fund_group_not_exist_for_management_fee() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FUND_GROUP_NOT_EXIST_FOR_MANAGEMENT_FEE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Active record for Fund Group %CODE% does not exist for Fee code 18.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Active record for Fund Group %CODE% does not exist for Fee code 18.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Active record for Fund Group %CODE% does not exist for Fee code 18.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'enregistrement actif du groupe de fonds %CODE% n'existe pas pour le code de frais 18.")); }

        // Actions
	};
}



