#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dicbocore_err_field_is_under_minimum_allowed : public CConditionObject
	{
	public:
		CIFast_IFast_dicbocore_err_field_is_under_minimum_allowed() { }
		~CIFast_IFast_dicbocore_err_field_is_under_minimum_allowed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FIELD_IS_UNDER_MINIMUM_ALLOWED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dicbocore")); }
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



