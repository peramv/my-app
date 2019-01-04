#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_cat_type_exists_for_acct : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_cat_type_exists_for_acct() { }
		~CIFast_IFast_ifastdbrkr_err_cat_type_exists_for_acct() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_CAT_TYPE_EXISTS_FOR_ACCT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Category Type already exists for this account.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Category Type already exists for this account.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Category Type already exists for this account.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le type de catégorie existe déjà pour ce compte.")); }

        // Actions
	};
}



