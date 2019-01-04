#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_ifastcbo_err_address_code_usedby_mailing : public CConditionObject
	{
	public:
		CIFast_Infrastructure_ifastcbo_err_address_code_usedby_mailing() { }
		~CIFast_Infrastructure_ifastcbo_err_address_code_usedby_mailing() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ADDRESS_CODE_USEDBY_MAILING")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Zip delivery sequence number is required for formatted addresses.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Zip delivery sequence number is required for formatted addresses.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Die Postleitzonenfolgenummer ist für die formatierte Adresse erforderlich .")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Se requiere el número de secuencia de entrega para las direcciones formateadas.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le numéro de séquence de livraison ZIP est requis pour les adresses mises en forme.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Volgnummer bestellingspostcode is  vereist voor ingedeelde adressen")); }

        // Actions
	};
}



