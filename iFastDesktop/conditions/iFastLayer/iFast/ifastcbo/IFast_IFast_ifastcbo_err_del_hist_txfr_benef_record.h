#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_del_hist_txfr_benef_record : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_del_hist_txfr_benef_record() { }
		~CIFast_IFast_ifastcbo_err_del_hist_txfr_benef_record() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_DEL_HIST_TXFR_BENEF_RECORD")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Delete beneficiary record(s) for historical RESP transferred-in notional balances for the QESI to change the value of this field.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Supprimez les enregistrements de bénéficiaires pour l'historique des soldes théoriques de transferts entrants REEE pour l'IQEE afin de changer la valeur de ce champ.")); }

        // Actions
	};
}



