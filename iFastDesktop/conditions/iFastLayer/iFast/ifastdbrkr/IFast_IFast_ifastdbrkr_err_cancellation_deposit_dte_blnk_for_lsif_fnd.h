#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_cancellation_deposit_dte_blnk_for_lsif_fnd : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_cancellation_deposit_dte_blnk_for_lsif_fnd() { }
		~CIFast_IFast_ifastdbrkr_err_cancellation_deposit_dte_blnk_for_lsif_fnd() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_CANCELLATION_DEPOSIT_DTE_BLNK_FOR_LSIF_FND")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Deposit date is blank for LSIF fund.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le champ de la date de dépôt est vide pour le fonds FIT.")); }

        // Actions
	};
}



