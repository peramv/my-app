#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_minimum_subsequent_amt : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_minimum_subsequent_amt() { }
		~CIFast_IFast_ifastcbo_err_minimum_subsequent_amt() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_MINIMUM_SUBSEQUENT_AMT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Minimum subsequent %TRADE_TYPE% amount for fund %FUND% and class %CLASS% is %MINIMUM_AMT%.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Le montant minimum de %TRADE_TYPE% ultérieur du fonds %FUND% et de la catégorie %CLASS% est %MINIMUM_AMT%")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Minimaler folgender  %TRADE_TYPE%-Betrag für Fonds %FUND% und Klasse %CLASS% beträgt %MINIMUM_AMT%")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El monto mínimo subsiguiente de %TRADE_TYPE% para el fondo %FUND% y la clase %CLASS% es de %MINIMUM_AMT%")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le montant %TRADE_TYPE% subséquent minimal pour le fonds %FUND% et la classe %CLASS% est %MINIMUM_AMT%.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Minimale volgende %TRADE_TYPE% bedrag voor fonds %FUND% en categorie %CLASS% is %MINIMUM_AMT%")); }

        // Actions
	};
}



