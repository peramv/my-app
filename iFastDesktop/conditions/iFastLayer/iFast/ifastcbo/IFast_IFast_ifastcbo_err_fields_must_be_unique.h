#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_fields_must_be_unique : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_fields_must_be_unique() { }
		~CIFast_IFast_ifastcbo_err_fields_must_be_unique() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FIELDS_MUST_BE_UNIQUE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("%FIELD1% and %FIELD2% must be unique.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Les zones %FIELD1% et %FIELD2% doivent être uniques. Veuillez resélectionner.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("%FIELD1% und %FIELD2% müssen eindeutig sein. Bitte wählen Sie neu.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("%FIELD1% y %FIELD2% deben ser únicos. Por favor vuelva a seleccionar los campos.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("%FIELD1% et %FIELD2% doivent être uniques.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("%FIELD1% en %FIELD2% moeten uniek zijn. Selecteer opnieuw")); }

        // Actions
	};
}



