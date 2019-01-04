﻿#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_rif_past_effective_date : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_rif_past_effective_date() { }
		~CIFast_IFast_ifastcbo_err_rif_past_effective_date() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_RIF_PAST_EFFECTIVE_DATE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("%ACCOUNT_TYPE% can be maintained for year %CURRENT_BUS_DATE% or later only.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("%ACCOUNT_TYPE% peut être maintenu uniquement pour l'annee %CURRENT_BUS_DATE% ou ulterieurement.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("%ACCOUNT_TYPE% kann nur für das Jahr %CURRENT_BUS_DATE% oder später gepflegt werden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("%ACCOUNT_TYPE% puede mantenerse para el año %CURRENT_BUS_DATE% o años posteriores solamente.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le %ACCOUNT_TYPE% ne peut être maintenu que pour l'année %CURRENT_BUS_DATE% ou les suivantes.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("%ACCOUNT_TYPE% kan alleen in stand gehouden worden voor het jaar %CURRENT_BUS_DATE% of later")); }

        // Actions
	};
}



