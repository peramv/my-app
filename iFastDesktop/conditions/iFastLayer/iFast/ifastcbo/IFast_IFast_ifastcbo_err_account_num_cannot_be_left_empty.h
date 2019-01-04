#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_account_num_cannot_be_left_empty : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_account_num_cannot_be_left_empty() { }
		~CIFast_IFast_ifastcbo_err_account_num_cannot_be_left_empty() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ACCOUNT_NUM_CANNOT_BE_LEFT_EMPTY")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The account number must be entered.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Le numero de compte doit être saisi.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Die Kontonummer muss eingegeben werden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Debe introducirse el número de cuenta.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le numéro de compte est requis.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Het accountnummer moet worden ingevoerd")); }

        // Actions
	};
}



