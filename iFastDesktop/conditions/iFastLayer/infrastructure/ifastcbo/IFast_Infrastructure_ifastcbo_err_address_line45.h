#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_ifastcbo_err_address_line45 : public CConditionObject
	{
	public:
		CIFast_Infrastructure_ifastcbo_err_address_line45() { }
		~CIFast_Infrastructure_ifastcbo_err_address_line45() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ADDRESS_LINE45")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Zip delivery office code is not allowed for unformatted addresses.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Zip delivery office code is not allowed for unformatted addresses.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Der Postamtcode ist für die unformatierte Adresse nicht zulässig.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se permite el código postal de la oficina de entrega para las direcciones no formateadas.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le code postal de bureau de livraison n'est pas autorisé pour les adresses postales qui ne sont pas mises en forme.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Postcode voor bestellingskantoor is niet toegestaan voor niet-ingedeelde adressen")); }

        // Actions
	};
}



