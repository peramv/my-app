#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_fund_class_for_management_fee_rebate : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_fund_class_for_management_fee_rebate() { }
		~CIFast_IFast_ifastcbo_err_fund_class_for_management_fee_rebate() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FUND_CLASS_FOR_MANAGEMENT_FEE_REBATE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The %FUNDCLASS% is not allowed for Fee Code, Management Fee Rebate.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Die %FUNDCLASS% ist nicht erlaubt für Provisionscode = Management-Provisionsrabatt.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se permite %FUNDCLASS% para el código de comisión = reembolso de comisión por administración.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La classe de fonds %FUNDCLASS% n'est pas autorisée à avoir un code de frais et une remise sur les frais de gestion.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("De %FUNDCLASS% is niet toegestaan voor kostencode = korting beheerkosten")); }

        // Actions
	};
}



