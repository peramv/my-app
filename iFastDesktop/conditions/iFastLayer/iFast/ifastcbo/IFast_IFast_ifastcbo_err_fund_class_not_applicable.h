#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_fund_class_not_applicable : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_fund_class_not_applicable() { }
		~CIFast_IFast_ifastcbo_err_fund_class_not_applicable() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FUND_CLASS_NOT_APPLICABLE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Amount type F or T only applicable for transfer to FEL fund.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Betragsart F oder T sind nur anwendbar für Transfer zu FEL-Fonds")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El tipo de monto F o T sólo se aplican a transferencias a un fondo FEL")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les types de montant F ou T ne sont applicables que pour le transfert vers un fonds avec frais initiaux.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Bedragtype 'F' of 'T' is alleen van toepassing voor overdracht naar FEL-fonds")); }

        // Actions
	};
}



