#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_rif_non_100_total_percentage : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_rif_non_100_total_percentage() { }
		~CIFast_IFast_ifastcbo_err_rif_non_100_total_percentage() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_RIF_NON_100_TOTAL_PERCENTAGE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Total for all funds must be 100.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Le total de tous les fonds doit s'elever a 100.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Die Summe für alle Fonds muss 100 ergeben.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El total para todos los fondos debe ser 100.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le total pour tous les fonds doit être 100.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Totaal voor alle fondsen moet 100 zijn")); }

        // Actions
	};
}



