#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Infrastructure_ditabuscore_err_zip_code_not_numeric : public CConditionObject
	{
	public:
		CBase_Infrastructure_ditabuscore_err_zip_code_not_numeric() { }
		~CBase_Infrastructure_ditabuscore_err_zip_code_not_numeric() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ZIP_CODE_NOT_NUMERIC")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("ditabuscore")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The zip code is not numeric.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("The zip code is not numeric.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Die Postleitzahl ist nicht nummerisch.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El código postal no es numérico.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le code postal n'est pas numérique.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("De postcode is niet numeriek")); }

        // Actions
	};
}



