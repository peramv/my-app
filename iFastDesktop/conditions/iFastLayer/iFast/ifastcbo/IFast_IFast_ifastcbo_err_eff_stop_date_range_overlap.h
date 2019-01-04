#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_eff_stop_date_range_overlap : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_eff_stop_date_range_overlap() { }
		~CIFast_IFast_ifastcbo_err_eff_stop_date_range_overlap() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_EFF_STOP_DATE_RANGE_OVERLAP")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Please change the effective and/or stop date.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Please change the effective and/or stop date.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Bitte ändern Sie das Effektiv- und/oder das Stoppdatum.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Por favor cambie la fecha de entrada en vigencia y/o la fecha de baja")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Veuillez changer la date d'entrée en vigueur ou la date d'arrêt.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Wijzig de ingangs- en/of einddatum")); }

        // Actions
	};
}



