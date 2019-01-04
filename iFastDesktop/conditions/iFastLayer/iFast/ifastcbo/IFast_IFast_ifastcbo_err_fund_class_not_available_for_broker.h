#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_fund_class_not_available_for_broker : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_fund_class_not_available_for_broker() { }
		~CIFast_IFast_ifastcbo_err_fund_class_not_available_for_broker() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FUND_CLASS_NOT_AVAILABLE_FOR_BROKER")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Fund %FUND%, class %CLASS% is not eligible for broker %BROKER%.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Fund and Class is not eligible for this broker.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Fonds und Klasse sind für diesen Broker nicht geeignet.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El fondo y la clase no son aptos para este corredor")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le fonds %FUND% et la classe %CLASS% ne sont pas admissibles pour le courtier %BROKER%.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Fonds en categorie komen niet in aanmerking voor deze makelaar")); }

        // Actions
	};
}



