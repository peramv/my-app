#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ditabuscore_err_city_name_required : public CConditionObject
	{
	public:
		CIFast_IFast_ditabuscore_err_city_name_required() { }
		~CIFast_IFast_ditabuscore_err_city_name_required() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_CITY_NAME_REQUIRED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ditabuscore")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Value cannot be zero.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("La zone %FIELDNAME% ne peut pas contenir la valeur zero. Veuillez ressaisir.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Der Wert darf nicht Null sein. Bitte geben Sie neu ein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El valor no puede ser cero. Por favor vuelva a introducir los datos.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La valeur ne peut être zéro.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Waarde kan niet nul zijn. Vul opnieuw in")); }

        // Actions
	};
}



