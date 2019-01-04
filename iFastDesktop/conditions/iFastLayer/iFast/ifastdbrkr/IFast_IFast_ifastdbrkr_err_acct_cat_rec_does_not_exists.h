#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_acct_cat_rec_does_not_exists : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_acct_cat_rec_does_not_exists() { }
		~CIFast_IFast_ifastdbrkr_err_acct_cat_rec_does_not_exists() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ACCT_CAT_REC_DOES_NOT_EXISTS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Account Category record does not exists.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Account Category record does not exists.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Account Category record does not exists.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'enregistrement de catégorie de compte n'existe pas.")); }

        // Actions
	};
}



