#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_taxonmin_suppfedtax_suppprovtax : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_taxonmin_suppfedtax_suppprovtax() { }
		~CIFast_IFast_ifastcbo_err_taxonmin_suppfedtax_suppprovtax() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_TaxOnMin_SuppFedTax_SuppProvTax")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Suppress Federal Tax and Suppress Provincial Tax must be NO if Tax on Min is YES.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Unterdrückung von Bundes- Steuer und Provinz-Steuer. Steuer muss NEIN sein, wenn W/H-Steuer auf Min JA ist.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Suprimir impuesto federal y provincial debe ser NO si Impuesto de retención sobre mínimo es SÍ")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La suppression des impôts fédéral et provincial doit être désactivée si l'imposition minimale est activée.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Federale belasting en provinciale belasting achterwege laten. Belasting moet NEE zijn als bronbelasting bij min. JA is")); }

        // Actions
	};
}



