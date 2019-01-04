#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_rif_ams_fund_fund_code : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_rif_ams_fund_fund_code() { }
		~CIFast_IFast_ifastcbo_err_rif_ams_fund_fund_code() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_RIF_AMS_FUND_FUND_CODE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Non AMS fund is entered for a AMS account.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("AMS fund is entered for a non-AMS account.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("AMS-Fonds für ein Nicht-AMS-Konto eingegeben.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Se introdujo un fondo AMS para una cuenta no AMS.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Un fonds sans SGP est saisi pour un compte SGP.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("BBD-fonds is opgegeven voor een niet-BBD-account")); }

        // Actions
	};
}



