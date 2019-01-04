#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_amt_type_cannot_settle_cur : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_amt_type_cannot_settle_cur() { }
		~CIFast_IFast_ifastcbo_err_amt_type_cannot_settle_cur() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_AMT_TYPE_CANNOT_SETTLE_CUR")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Amount Type can not be the Settle Currency if muti-currency flag is switched off.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Betragsart kann nicht die Abrechnungswährung sein, wenn das Kennzeichen für Mehrere-Währungen deaktiviert ist.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El tipo de monto no puede ser la divisa de liquidación si se desactiva el flag multidivisa.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le type de montant ne peut être la monnaie de règlement si le signal multidevise est désactivé.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Bedragtype kan niet de betalingsvaluta zijn als de vlag voor meerdere valuta is uitgezet")); }

        // Actions
	};
}



