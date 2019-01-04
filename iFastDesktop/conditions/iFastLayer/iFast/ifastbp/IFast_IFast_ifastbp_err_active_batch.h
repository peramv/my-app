#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastbp_err_active_batch : public CConditionObject
	{
	public:
		CIFast_IFast_ifastbp_err_active_batch() { }
		~CIFast_IFast_ifastbp_err_active_batch() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ACTIVE_BATCH")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastbp")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("There are still active batches: %MSG%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Il y a encore des lots actifs : %MSG%.")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Please close all of them before logging off.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Veuillez tous les fermer avant de fermer votre session.")); }
	};
}



