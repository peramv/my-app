#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_address_id_not_found : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_address_id_not_found() { }
		~CIFast_IFast_ifastcbo_err_address_id_not_found() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ADDRESS_ID_NOT_FOUND")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("No matching address found for ID %ADDRESSID%. Leave this field blank if you are not sure of the ID.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Aucune adresse correspondante n'a ete trouvee pour l'identification %ADDRESSID%. Laissez cette zone vide.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Keine übereinstimmende Adresse für ID %ADDRESSID% gefunden. Lassen Sie dieses Feld leer, wenn Sie die ID nicht kennen.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se encontró ninguna dirección coincidente para la identificación %ADDRESSID%. Deje este campo en blanco si no está seguro de la identificación.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Aucune adresse correspondante n'a été trouvée pour le code %ADDRESSID%. Laissez ce champ vierge si vous êtes incertain du code.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er is geen overeenkomend adres gevonden voor ID %ADDRESSID%. Laat dit veld leeg als u niet zeker bent van het ID")); }

        // Actions
	};
}



