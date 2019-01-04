#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_field_inactive_as_of_trade_date : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_field_inactive_as_of_trade_date() { }
		~CIFast_IFast_ifastcbo_err_field_inactive_as_of_trade_date() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FIELD_INACTIVE_AS_OF_TRADE_DATE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("%FIELDNAME% is not active as of trade date.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("La zone %FIELDNAME% n'est pas active a compter de la date d'operation. Veuillez ressaisir %FIELDNAME% ou sélectionner une autre date d'operation")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("%FIELDNAME% ist nicht ab dem Handelsdatum aktiv. Bitte geben Sie  %FIELDNAME% neu ein oder wählen Sie ein anderes Handelsdatum.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("%FIELDNAME% no está activo a la fecha de transacción. Por favor vuelva a introducir el %FIELDNAME% o seleccione otra fecha de transacción")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le champ %FIELDNAME% est inactif en date de la transaction.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("%FIELDNAME% is niet actief vanaf de handelsdatum. Vul %FIELDNAME% opnieuw in of selecteer een andere handelsdatum")); }

        // Actions
	};
}



