#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_rif_cash_fund_code : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_rif_cash_fund_code() { }
		~CIFast_IFast_ifastcbo_err_rif_cash_fund_code() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_RIF_CASH_FUND_CODE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Fund Code value must not be \"Cash\".")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Fund Code value must not be \"Cash\".")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Fondscode-Wert darf nicht \"Bargeld\" sein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El valor del código de fondo no puede ser \"Efectivo\".")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La valeur du champ Code de fonds ne doit pas être Comptant.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Waarde voor fondscode mag niet 'Contant' zijn")); }

        // Actions
	};
}



