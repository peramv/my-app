﻿#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_rif_out_of_limits_percentage : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_rif_out_of_limits_percentage() { }
		~CIFast_IFast_ifastcbo_err_rif_out_of_limits_percentage() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_RIF_OUT_OF_LIMITS_PERCENTAGE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Percentage value must be between 0 and 100.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Le pourcentage doit être compris entre 0 et 100.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Prozentsatz muss zwischen 0 und 100 liegen.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El porcentaje debe ser entre 0 y 100.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La valeur de pourcentage doit être située entre 0 et 100.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Percentage moet tussen 0 en 100 liggen")); }

        // Actions
	};
}



