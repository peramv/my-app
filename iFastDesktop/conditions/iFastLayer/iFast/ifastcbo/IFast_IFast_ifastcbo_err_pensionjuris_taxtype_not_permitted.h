#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_pensionjuris_taxtype_not_permitted : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_pensionjuris_taxtype_not_permitted() { }
		~CIFast_IFast_ifastcbo_err_pensionjuris_taxtype_not_permitted() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_PENSIONJURIS_TAXTYPE_NOT_PERMITTED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Combination of Pension Jurisdiction and Tax Type is not permitted.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Diese Kombination von Renten-Rechtssprechung und Steuerart ist nicht erlaubt.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se permite esta combinación de jurisdicción de jubilación y tipo tributario.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Combinaison de juridiction de retraite et de type d'imposition non autorisée")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Combinatie van pensioenrechtsgebied en belastingtype is niet toegestaan")); }

        // Actions
	};
}



