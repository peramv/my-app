﻿#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_date_functions : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_date_functions() { }
		~CIFast_IFast_ifastcbo_err_date_functions() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_DATE_FUNCTIONS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Effective date must be after Initial Effective Date.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Comparing dates returned an error.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Der Datumsvergleich ergab einen Fehler.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La comparación de fechas devolvió un error.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La date d'entrée en vigueur doit être postérieure à la date d'entrée en vigueur initiale.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Het vergelijken van datums heeft een fout gegenereerd")); }

        // Actions
	};
}



