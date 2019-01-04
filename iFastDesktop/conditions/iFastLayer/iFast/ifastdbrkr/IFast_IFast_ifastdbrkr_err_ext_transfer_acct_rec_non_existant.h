#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_ext_transfer_acct_rec_non_existant : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_ext_transfer_acct_rec_non_existant() { }
		~CIFast_IFast_ifastdbrkr_err_ext_transfer_acct_rec_non_existant() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_EXT_TRANSFER_ACCT_REC_NON_EXISTANT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Account external transfer record does not exist.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Account external transfer record does not exist.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Account external transfer record does not exist.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'enregistrement du transfert externe du compte n'existe pas.")); }

        // Actions
	};
}



