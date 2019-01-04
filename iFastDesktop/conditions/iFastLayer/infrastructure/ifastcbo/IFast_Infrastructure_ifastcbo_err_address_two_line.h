#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_ifastcbo_err_address_two_line : public CConditionObject
	{
	public:
		CIFast_Infrastructure_ifastcbo_err_address_two_line() { }
		~CIFast_Infrastructure_ifastcbo_err_address_two_line() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ADDRESS_TWO_LINE")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Zip delivery office code is required for formatted addresses.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Zip delivery office code is required for formatted addresses.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Der Postamtcode ist für die formatierte Adresse erforderlich.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Se requiere el código postal de la oficina de entrega para las direcciones formateadas.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le code postal de bureau de livraison est requis pour les adresses postales mises en forme.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Postcode voor bestellingskantoor is vereist voor ingedeelde adressen")); }

        // Actions
	};
}



