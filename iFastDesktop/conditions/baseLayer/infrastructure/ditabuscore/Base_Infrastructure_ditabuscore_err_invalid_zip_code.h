#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Infrastructure_ditabuscore_err_invalid_zip_code : public CConditionObject
	{
	public:
		CBase_Infrastructure_ditabuscore_err_invalid_zip_code() { }
		~CBase_Infrastructure_ditabuscore_err_invalid_zip_code() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_ZIP_CODE")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("ditabuscore")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The zip code is invalid.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("The zip code is invalid.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Die Postleitzahl ist ungültig.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El código postal no es válido.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Code postal invalide")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("De postcode is ongeldig")); }

        // Actions
	};
}



