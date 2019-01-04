#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_sys_trig_amend_and_recal_qesi_notional_balance : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_sys_trig_amend_and_recal_qesi_notional_balance() { }
		~CIFast_IFast_ifastcbo_warn_sys_trig_amend_and_recal_qesi_notional_balance() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_SYS_TRIG_AMEND_AND_RECAL_QESI_NOTIONAL_BALANCE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("System will trigger amendment and recalculate QESI notional balance for the tax year.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le système va déclencher un amendement et recalculer le solde théorique IQEE pour l'année d'imposition.")); }

        // Actions
	};
}



