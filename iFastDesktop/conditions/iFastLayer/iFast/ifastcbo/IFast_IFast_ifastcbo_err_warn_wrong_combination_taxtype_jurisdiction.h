#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_warn_wrong_combination_taxtype_jurisdiction : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_warn_wrong_combination_taxtype_jurisdiction() { }
		~CIFast_IFast_ifastcbo_err_warn_wrong_combination_taxtype_jurisdiction() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_WARN_WRONG_COMBINATION_TAXTYPE_JURISDICTION")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Tax Type %TAXTYPE% is not offered by the Tax Jurisdiction %TAXJURIS% of the shareholder.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Steuerart %TAXTYPE% wird nicht von der Steuer-Rechtssprechung %TAXJURIS% des Aktionärs angeboten.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El tipo tributario %TAXTYPE% no es ofrecido por la jurisdicción tributaria %TAXJURIS% del accionista")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le type d'imposition %TAXTYPE% n'est pas disponible avec la juridiction fiscale %TAXJURIS% de l'actionnaire.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Belastingtype TAXTYPE% wordt niet aangeboden in het belastingrechtsgebied %TAXJURIS% van de aandeelhouder")); }

        // Actions
	};
}



