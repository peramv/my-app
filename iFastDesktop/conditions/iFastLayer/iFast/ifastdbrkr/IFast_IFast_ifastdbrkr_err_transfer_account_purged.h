#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_transfer_account_purged : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_transfer_account_purged() { }
		~CIFast_IFast_ifastdbrkr_err_transfer_account_purged() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_TRANSFER_ACCOUNT_PURGED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Matching transfer account has been purged, cannot cancel.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Matching transfer account has been purged, cannot cancel.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le compte de transfert correspondant a été éliminé, annulation impossible.")); }

        // Actions
	};
}



