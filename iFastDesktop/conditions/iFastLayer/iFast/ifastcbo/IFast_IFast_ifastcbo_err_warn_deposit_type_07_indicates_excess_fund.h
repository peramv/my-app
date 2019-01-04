#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_warn_deposit_type_07_indicates_excess_fund : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_warn_deposit_type_07_indicates_excess_fund() { }
		~CIFast_IFast_ifastcbo_err_warn_deposit_type_07_indicates_excess_fund() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_WARN_DEPOSIT_TYPE_07_INDICATES_EXCESS_FUND")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Deposit type 07 indicates transfer of excess funds.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Depot-Typ 07 zeigt den Transfer von Überschussfonds an.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El tipo de depósito 07 indica transferencia de fondos excedentes.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le code de dépôt 07 indique le transfert des fonds excédentaires.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Depositotype 07 geeft overdracht van surplusfondsen aan")); }

        // Actions
	};
}



