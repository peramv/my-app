#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_as_of_date_was_not_entered : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_as_of_date_was_not_entered() { }
		~CIFast_IFast_ifastdbrkr_err_as_of_date_was_not_entered() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_AS_OF_DATE_WAS_NOT_ENTERED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("As of date was not entered.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("As of date was not entered.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("“Mit Wirkung vom…”-Datum war nicht eingetragen")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se introdujo la fecha Hasta")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Cette date n'a pas été saisie.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Vanaf-datum is niet ingevoerd")); }

        // Actions
	};
}



