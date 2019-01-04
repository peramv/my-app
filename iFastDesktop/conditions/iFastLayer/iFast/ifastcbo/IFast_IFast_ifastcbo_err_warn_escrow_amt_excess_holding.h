#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_warn_escrow_amt_excess_holding : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_warn_escrow_amt_excess_holding() { }
		~CIFast_IFast_ifastcbo_err_warn_escrow_amt_excess_holding() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_WARN_ESCROW_AMT_EXCESS_HOLDING")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Escrow/Assigned amount exceeds current settled value:  %SETTLEVALUE%.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Treuhand-Betrag übersteigt den aktuellen abgerechneten Wert:  %SETTLEVALUE%")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El monto en custodia excede el valor liquidado actual:  %SETTLEVALUE%")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le montant de la mise en garantie excède la valeur réglée actuelle : %SETTLEVALUE%.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Pandbedrag overschrijdt huidige betalingswaarde:  %SETTLEVALUE%")); }

        // Actions
	};
}



