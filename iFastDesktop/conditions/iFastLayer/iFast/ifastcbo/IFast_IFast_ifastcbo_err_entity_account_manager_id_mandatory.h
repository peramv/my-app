#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_entity_account_manager_id_mandatory : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_entity_account_manager_id_mandatory() { }
		~CIFast_IFast_ifastcbo_err_entity_account_manager_id_mandatory() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ACCOUNT_MANAGER_ID_MANDATORY")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Account Manager Unique ID is mandatory for this Entity type.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Pour cette entité, Account Manager Unique ID est obligatoire.")); }

        // Actions
	};
}



