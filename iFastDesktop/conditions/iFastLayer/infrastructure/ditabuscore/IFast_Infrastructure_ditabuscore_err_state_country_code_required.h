#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_ditabuscore_err_state_country_code_required : public CConditionObject
	{
	public:
		CIFast_Infrastructure_ditabuscore_err_state_country_code_required() { }
		~CIFast_Infrastructure_ditabuscore_err_state_country_code_required() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_STATE_COUNTRY_CODE_REQUIRED")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("ditabuscore")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("State country code must be set for postal address.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("State country code must be set for postal address.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Der Staat-/Ländercode muss für eine Postadresse festgelegt sein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Debe definirse el código de estado/país para la dirección postal.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le code de pays de l'état/de la province doit être réglé pour l'adresse postale.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Staat/landcode moet zijn ingesteld voor postadres")); }

        // Actions
	};
}



