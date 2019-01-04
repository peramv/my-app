#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_invalid_amttype_for_bel_redemption : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_invalid_amttype_for_bel_redemption() { }
		~CIFast_IFast_ifastcbo_err_invalid_amttype_for_bel_redemption() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_AMTTYPE_FOR_BEL_REDEMPTION")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Amount Type %AMT_TYPE% only applicable to back end load redemption.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Ungültige Betragsart für Hohe-Endkostentilgung")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Tipo de monto no válido para rescate de cargo de venta final")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le type de montant %AMT_TYPE% n'est applicable qu'aux rachats avec frais de rachat.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Ongeldig bedragtype voor aflossing back end load")); }

        // Actions
	};
}



