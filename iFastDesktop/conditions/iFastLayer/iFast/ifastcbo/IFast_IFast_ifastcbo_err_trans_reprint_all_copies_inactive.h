#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_trans_reprint_all_copies_inactive : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_trans_reprint_all_copies_inactive() { }
		~CIFast_IFast_ifastcbo_err_trans_reprint_all_copies_inactive() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_TRANS_REPRINT_ALL_COPIES_INACTIVE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("At least one copy must be setup for Reprint.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("At least one copy must be setup for Reprint.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Au moins une copie doit être réglée pour la réimpression.")); }

        // Actions
	};
}



