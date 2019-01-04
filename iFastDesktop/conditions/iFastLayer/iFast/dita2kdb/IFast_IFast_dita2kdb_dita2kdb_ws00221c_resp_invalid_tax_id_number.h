#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_tax_id_number : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_tax_id_number() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_tax_id_number() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_INVALID_TAX_ID_NUMBER")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Units is not allowed for EFT Purchase.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("La méthode de paiement débit du compte n'est pas alloué pour les  achats en unités.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Anteile nicht erlaubt für EFT-Kauf.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se permiten unidades para una compra EFT")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les unités ne sont pas autorisées pour un achat TEF.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Eenheden zijn niet toegestaan voor EFO-aankoop")); }

        // Actions
	};
}



