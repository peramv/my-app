#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_fund_class_for_management_fee : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_fund_class_for_management_fee() { }
		~CIFast_IFast_ifastcbo_err_fund_class_for_management_fee() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FUND_CLASS_FOR_MANAGEMENT_FEE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The %FUNDCLASS% is not allowed for Fee Code, Daily Management Fee.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Die %FUNDCLASS% ist nicht erlaubt für Provisionscode = Tägliche Management-Provision.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se permite %FUNDCLASS% para el código de comisión = comisión por administración diaria.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La classe de fonds %FUNDCLASS% n'est pas autorisée à avoir un code de frais et des frais de gestion quotidiens.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("De %FUNDCLASS% is niet toegestaan voor kostencode = kosten dagelijks beheer")); }

        // Actions
	};
}



