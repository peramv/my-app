#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_wrong_combination_taxtype_jurisdiction : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_wrong_combination_taxtype_jurisdiction() { }
		~CIFast_IFast_ifastcbo_err_wrong_combination_taxtype_jurisdiction() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_WRONG_COMBINATION_TAXTYPE_JURISDICTION")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Tax Type is not allowed for the tax or pension jurisdiction.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Steuertyp für die Steuer- oder Renten-Rechtssprechung ist nicht erlaubt .")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se permite el tipo tributario para la jurisdicción tributaria o de jubilación.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Type d'imposition non autorisé pour la juridiction fiscale ou la juridiction de retraite")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Belastingtype is niet toegestaan voor het belasting- of het pensioenrechtsgebied")); }

        // Actions
	};
}



