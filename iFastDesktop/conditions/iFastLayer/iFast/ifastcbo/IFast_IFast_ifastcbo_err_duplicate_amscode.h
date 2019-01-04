#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_duplicate_amscode : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_duplicate_amscode() { }
		~CIFast_IFast_ifastcbo_err_duplicate_amscode() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_DUPLICATE_AMSCODE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("AMS Code %AMSCODE% is not unique.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("AMS-Code %AMSCODE% ist nicht eindeutig.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El código AMS %AMSCODE% ni es único.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le code de service de gestion de portefeuille %AMSCODE% n'est pas unique.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("BBD-code %AMSCODE% is niet uniek")); }

        // Actions
	};
}



