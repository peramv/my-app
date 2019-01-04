#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_warn_red_amt_more_than_holding : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_warn_red_amt_more_than_holding() { }
		~CIFast_IFast_ifastcbo_err_warn_red_amt_more_than_holding() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_WARN_RED_AMT_MORE_THAN_HOLDING")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The redemption amount entered for fund %FUNDNAME% %CLASSNAME% exceeds the current holding in this account.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Der Tilgungs-Betrag, der für den Fonds %FUNDNAME% eingegeben wurde, übersteigt seine aktuelle Beteiligung an diesem Konto.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El monto de rescate introducido para el fondo %FUNDNAME% excede las tenencias actuales en este fondo.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le montant de rachat saisi pour le fonds %FUNDNAME% et la classe %CLASSNAME% excède le portefeuille actuel de ce compte.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Het aflossingsbedrag dat is ingevuld voor fonds %FUNDNAME% overschrijdt het huidige vermogen in dit account")); }

        // Actions
	};
}



