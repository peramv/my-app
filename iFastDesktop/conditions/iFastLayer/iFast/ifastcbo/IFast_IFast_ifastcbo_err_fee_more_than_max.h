#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_fee_more_than_max : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_fee_more_than_max() { }
		~CIFast_IFast_ifastcbo_err_fee_more_than_max() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FEE_MORE_THAN_MAX")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Fee greater than maximum fee allowed for fund %FUNDNAME% %CLASS%.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Les frais de souscription spécifiés dépassent le maximum alloué pour le fonds %FUNDNAME% %CLASS%.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Provision größer als maximal erlaubte Provision für Fonds %FUNDNAME% %CLASS%.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La comisión es mayor que la comisión máxima permitida para el fondo %FUNDNAME% %CLASS%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les frais excèdent les frais maximaux autorisés pour le fonds %FUNDNAME% %CLASS%.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Kosten zijn hoger dan de toegestane maximumkosten voor fonds %FUNDNAME% %CLASS%")); }

        // Actions
	};
}



