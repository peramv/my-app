#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_fund_can_not_be_blank : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_fund_can_not_be_blank() { }
		~CIFast_IFast_ifastcbo_err_fund_can_not_be_blank() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FUND_CAN_NOT_BE_BLANK")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("From fund must be entered for %TRADE_TYPE%.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Le fonds de (depart) doit être saisi pour le %TRADE_TYPE%. Veuillez sélectionner un fonds.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Von-Fund muss eingegeben werden für %TRADE_TYPE% . Bitte wählen Sie einen Fonds.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Debe introducirse el fondo de origen para %TRADE_TYPE%. Por favor seleccione un fondo.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le champ Du fonds doit être rempli pour %TRADE_TYPE%.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Van-fonds moet worden ingevoerd voor %TRADE_TYPE%. Selecteer een fonds")); }

        // Actions
	};
}



