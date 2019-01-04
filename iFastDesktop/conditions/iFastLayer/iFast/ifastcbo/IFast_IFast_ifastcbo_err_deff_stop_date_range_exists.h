#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_deff_stop_date_range_exists : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_deff_stop_date_range_exists() { }
		~CIFast_IFast_ifastcbo_err_deff_stop_date_range_exists() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_DEFF_STOP_DATE_RANGE_EXISTS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Another %CODE% address exists for the date range indicated. Please select a different Effective and Stop date or an unused address code.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Une autre adresse %CODE% existe pour la plage de dates specifiee. Veuillez sélectionner une date d'effet et d'arret ou un code d'adresse non utilise.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Für den angegebenen Datumsbereich existiert eine weitere %CODE%–Adresse . Bitte wählen Sie ein anderes Effektiv- oder Stopdatum oder einen noch nicht verwendeten Adresscode.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Existe otra dirección %CODE% para el rango de fechas indicado. Por favor seleccione otra fecha de entrada en vigencia y baja o un código de dirección no utilizado.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Une autre adresse %CODE% existe pour la plage de dates indiquée. Veuillez sélectionner des dates d'entrée en vigueur et d'arrêt différentes ou un code d'adresse inutilisé.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er bestaat een ander %CODE% adres voor het aangegeven datumbereik. Selecteer een andere ingangs- en einddatum of een ongebruikte adrescode")); }

        // Actions
	};
}



