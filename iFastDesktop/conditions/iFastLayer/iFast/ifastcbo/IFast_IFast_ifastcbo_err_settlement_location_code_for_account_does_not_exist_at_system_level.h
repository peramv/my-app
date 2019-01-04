#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_settlement_location_code_for_account_does_not_exist_at_system_level : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_settlement_location_code_for_account_does_not_exist_at_system_level() { }
		~CIFast_IFast_ifastcbo_err_settlement_location_code_for_account_does_not_exist_at_system_level() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_SETTLEMENT_LOCATION_CODE_FOR_ACCOUNT_DOES_NOT_EXIST_AT_SYSTEM_LEVEL")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("At least one Settlement Location Code defined at Acct Level is not defined at System Level.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("At least one Settlement Location Code defined at Acct Level is not defined at System Level.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("At least one Settlement Location Code defined at Acct Level is not defined at System Level.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Au moins un des codes de lieu de règlement définis au niveau du compte n'est pas défini au niveau du système.")); }

        // Actions
	};
}



