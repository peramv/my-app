#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_rif_only_one_good_record : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_rif_only_one_good_record() { }
		~CIFast_IFast_ifastcbo_err_rif_only_one_good_record() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_RIF_ONLY_ONE_GOOD_RECORD")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("%ACCOUNT_TYPE% already exists for year %EFFECTIVE_DATE%.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("%ACCOUNT_TYPE% already exists for year %EFFECTIVE_DATE%.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("%ACCOUNT_TYPE% existiert bereits für das Jahr %EFFECTIVE_DATE%.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("%ACCOUNT_TYPE% ya existe para el año %EFFECTIVE_DATE%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le %ACCOUNT_TYPE% existe déjà pour l'année %EFFECTIVE_DATE%.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("%ACCOUNT_TYPE% bestaat al voor jaar %EFFECTIVE_DATE%")); }

        // Actions
	};
}



